#include <cassert>

#if defined ( _WIN32 )
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <MyLib/make_unique.hpp>
#include "ipcclient.hpp"


#define     MSG_RECEIVED        "RCVD!"


using namespace MyLib;

IPCClient::IPCClient() :
    m_running(false),
    m_remotePort(0)
{
}

IPCClient::IPCClient(const std::string &id, const std::string &remoteHost, port_t remotePort) :
    m_id(id),
    m_running(false),
    m_remoteHost(remoteHost),
    m_remotePort(remotePort)
{
}

IPCClient::~IPCClient()
{
    if (m_running) {
        Stop();
    }
}

std::string IPCClient::GetId() const
{
    return m_id;
}

std::string IPCClient::GetRemoteHost() const
{
    return m_remoteHost;
}

IPCClient::port_t IPCClient::GetRemotePort() const
{
    return m_remotePort;
}

void IPCClient::SetId(const std::string &id)
{
    if (m_running)
        return;

    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    m_id = id;
}

void IPCClient::SetRemoteHost(const std::string &remoteHost)
{
    if (m_running)
        return;

    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    m_remoteHost = remoteHost;
}

void IPCClient::SetRemotePort(port_t remotePort)
{
    if (m_running)
        return;

    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    m_remotePort = remotePort;
}

bool IPCClient::IsRunning() const
{
    return m_running;
}

void IPCClient::Start()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    assert(boost::algorithm::trim_copy(m_id) != "");
    assert(boost::algorithm::trim_copy(m_remoteHost) != "");
    assert(m_remotePort != 0);

    if (m_running) {
        return;
    }

    std::string tcpURL((boost::format("tcp://%1%:%2%")
                        % m_remoteHost
                        % boost::lexical_cast<std::string>(m_remotePort)).str());

    m_context = std::make_unique<zmq::context_t>(1);
    m_socket = std::make_unique<zmq::socket_t>(*m_context.get(), ZMQ_REQ);

    int linger = 0;
    m_socket->setsockopt(ZMQ_LINGER, &linger, sizeof(linger));

    m_socket->connect(tcpURL.c_str());

    m_running = true;

    m_workerThread = std::make_unique<boost::thread>(&IPCClient::SendRequests, this);
    m_workerThread->detach();
}

void IPCClient::Stop()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    if (!m_running) {
        return;
    }

    m_running = false;
    m_workerThread->interrupt();

    std::string tcpURL((boost::format("tcp://%1%:%2%")
                        % m_remoteHost
                        % boost::lexical_cast<std::string>(m_remotePort)).str());
    zmq_disconnect((void *)m_socket.get(), tcpURL.c_str());

    try {
        m_socket->close();
        m_context->close();
    } catch(...) {
    }

    m_workerThread.reset();
    m_socket.reset();
    m_context.reset();
}

void IPCClient::SendMessage(const std::string &message)
{
    if (!m_running)
        return;

    std::lock_guard<std::mutex> lock(m_dataMutex);
    (void)lock;

    m_requests.push(message);
}

std::string IPCClient::GetMessage(const zmq::message_t &message)
{
    return std::string(static_cast<const char *>(message.data()), message.size());
}

void IPCClient::SendRequest(const std::string &request)
{
    boost::property_tree::ptree reqTree;
    reqTree.put("req.clientId", m_id);
    reqTree.put("req.message", request);

    std::stringstream reqStream;
    boost::property_tree::write_json(reqStream, reqTree);
    std::string reqJSON(reqStream.str());

    zmq::message_t req(reqJSON.size());
    memcpy(req.data(), reqJSON.data(), reqJSON.size());

    bool rc = false;
    do {
        boost::this_thread::disable_interruption di;

        try {
            std::lock_guard<std::mutex> lock(m_workerMutex);
            (void)lock;

            rc = m_socket->send(req, ZMQ_NOBLOCK);
        } catch (...){
        }

        if (rc) {
            zmq::message_t res;
            do {
                try {
                    std::lock_guard<std::mutex> lock(m_workerMutex);
                    (void)lock;

                    rc = m_socket->recv(&res, ZMQ_NOBLOCK);
                } catch (...){
                }

                if (rc) {
                    if (GetMessage(res) == MSG_RECEIVED) {
                        if (OnMessageSent) {
                            OnMessageSent(request);
                        }
                    }
                }

                boost::this_thread::restore_interruption ri(di);
                boost::this_thread::interruption_point();
            } while (!rc);
        }

        boost::this_thread::restore_interruption ri(di);
        boost::this_thread::interruption_point();
    } while (!rc);
}

void IPCClient::SendRequests()
{
    while(m_running) {
        if (m_requests.size() > 0) {
            std::string message;

            {
                std::lock_guard<std::mutex> lock(m_dataMutex);
                (void)lock;

                message = m_requests.front();
                m_requests.pop();
            }

            SendRequest(message);
        } else {
#if defined ( _WIN32 )
            Sleep(1);
#else
            sleep(1);
#endif
        }

        boost::this_thread::interruption_point();
    }
}

