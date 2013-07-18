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
#include "ipcclient.hpp"
#include "log.hpp"
#include "make_unique.hpp"

using namespace MyLib;

IPCClient::IPCClient() :
    m_running(false),
    m_remotePort(0)
{
}

IPCClient::IPCClient(const std::string &id, const std::string &remoteHost, port_t remotePort) :
    m_running(false),
    m_remoteHost(remoteHost),
    m_remotePort(remotePort)
{
}

IPCClient::~IPCClient()
{
    m_workerMutex.lock();
    if (m_running) {
        m_workerMutex.unlock();
        Stop();
    } else {
        m_workerMutex.unlock();
    }
}

std::string IPCClient::GetRemoteHost()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    return m_remoteHost;
}

IPCClient::port_t IPCClient::GetRemotePort()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    return m_remotePort;
}

void IPCClient::SetRemoteHost(const std::string &remoteHost)
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    if (m_running)
        return;

    m_remoteHost = remoteHost;
}

void IPCClient::SetRemotePort(port_t remotePort)
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    if (m_running)
        return;

    m_remotePort = remotePort;
}

bool IPCClient::IsRunning()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    return m_running;
}

void IPCClient::Start()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

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
        LOG_ERROR("...");
    }

    m_workerThread.reset();
    m_socket.reset();
    m_context.reset();
}


void IPCClient::SendRequest(Compression::CompressionBuffer_t &buffer, Callback_t &callback)
{
    zmq::message_t req(buffer.size());
    memcpy(buffer.data(), buffer.data(), buffer.size());

    bool rc = false;
    do {
        boost::this_thread::disable_interruption di;

        try {
            std::lock_guard<std::mutex> lock(m_workerMutex);
            (void)lock;

            rc = m_socket->send(req, ZMQ_NOBLOCK);
        } catch (...){
            LOG_ERROR("...");
        }

        if (rc) {
            zmq::message_t response;
            do {
                try {
                    std::lock_guard<std::mutex> lock(m_workerMutex);
                    (void)lock;

                    rc = m_socket->recv(&response, ZMQ_NOBLOCK);
                } catch (...){
                    LOG_ERROR("...");
                }

                if (rc) {
                    const Compression::CompressionBuffer_t
                            buffer(static_cast<const char *>(response.data())[0], response.size());
                    boost::bind(callback, buffer);
                    callback();
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
    m_workerMutex.lock();
    while(m_running) {
        m_workerMutex.unlock();

        m_dataMutex.lock();
        if (m_reqBuffers.size() > 0) {
            m_dataMutex.unlock();

            Compression::CompressionBuffer_t buffer;
            Callback_t callback;

            {
                std::lock_guard<std::mutex> lock(m_dataMutex);
                (void)lock;

                buffer = m_reqBuffers.front();
                callback = m_reqCallbacks.front();
            }

            SendRequest(buffer, callback);

            {
                std::lock_guard<std::mutex> lock(m_dataMutex);
                (void)lock;

                m_reqBuffers.pop();
                m_reqCallbacks.pop();
            }
        } else {
            m_dataMutex.unlock();
        }

        boost::this_thread::interruption_point();
        m_workerMutex.lock();
    }
}

