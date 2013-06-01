#include <cassert>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <MyLib/make_unique.hpp>
#include "ipcclient.hpp"

using namespace MyLib;

const std::string IPCClient::MSG_RECEIVED = "RCVD!";

IPCClient::IPCClient() :
    m_running(false),
    m_port(0)
{
}

IPCClient::IPCClient(const std::string &id, port_t port) :
    m_id(id),
    m_running(false),
    m_port(port)
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

IPCClient::port_t IPCClient::GetPort() const
{
    return m_port;
}

void IPCClient::SetId(const std::string &id)
{
    if (m_running)
        return;

    m_workerMutex.lock();
    m_id = id;
    m_workerMutex.unlock();
}

void IPCClient::SetPort(port_t port)
{
    if (m_running)
        return;

    m_workerMutex.lock();
    m_port = port;
    m_workerMutex.unlock();
}

bool IPCClient::IsRunning() const
{
    return m_running;
}

void IPCClient::Start()
{
    m_workerMutex.lock();

    assert(boost::algorithm::trim_copy(m_id) != "");
    assert(m_port != 0);

    if (m_running) {
        m_workerMutex.unlock();
        return;
    }

    std::string tcpURL((boost::format("tcp://localhost:%1%") % boost::lexical_cast<std::string>(m_port)).str());

    m_context = std::make_unique<zmq::context_t>(1);
    m_socket = std::make_unique<zmq::socket_t>(*m_context.get(), ZMQ_REQ);

    int linger = 0;
    m_socket->setsockopt(ZMQ_LINGER, &linger, sizeof(linger));

    m_socket->connect(tcpURL.c_str());

    m_running = true;

    m_workerThread = std::make_unique<boost::thread>(&IPCClient::SendRequests, this);
    m_workerThread->detach();

    m_workerMutex.unlock();
}

void IPCClient::Stop()
{
    m_workerMutex.lock();

    if (!m_running) {
        m_workerMutex.unlock();
        return;
    }

    m_running = false;
    m_workerThread->interrupt();

    std::string tcpURL((boost::format("tcp://localhost:%1%") % boost::lexical_cast<std::string>(m_port)).str());
    zmq_disconnect((void *)m_socket.get(), tcpURL.c_str());

    try {
        m_socket->close();
        m_context->close();
    } catch(...) {
    }

    m_workerThread.reset();
    m_socket.reset();
    m_context.reset();

    m_workerMutex.unlock();
}

void IPCClient::SendMessage(const std::string &message)
{
    if (!m_running)
        return;

    m_dataMutex.lock();
    m_requests.push(message);
    m_dataMutex.unlock();
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
        m_workerMutex.lock();
        try {
            rc = m_socket->send(req, ZMQ_NOBLOCK);
        } catch (...){
        }
        m_workerMutex.unlock();

        if (rc) {
            zmq::message_t res;
            do {
                m_workerMutex.lock();
                try {
                    rc = m_socket->recv(&res, ZMQ_NOBLOCK);
                } catch (...){
                }
                m_workerMutex.unlock();

                if (rc) {
                    if (GetMessage(res) == IPCClient::MSG_RECEIVED) {
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
            m_dataMutex.lock();
            std::string messageStr(m_requests.front());
            m_requests.pop();
            m_dataMutex.unlock();
            SendRequest(messageStr);
        }
        boost::this_thread::interruption_point();
    }
}

