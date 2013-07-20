#include <chrono>
#include <cassert>

#if defined ( _WIN32 )
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "ipcclient.hpp"
#include "log.hpp"
#include "make_unique.hpp"

#define     IPC_TIMEOUT         10

using namespace MyLib;

IPCClient::IPCClient() :
    m_running(false),
    m_remotePort(0)
{
}

IPCClient::IPCClient(const std::string &remoteHost, port_t remotePort) :
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


void IPCClient::SendARequest(const std::string &request, Callback_t callback)
{
    zmq::message_t req(request.size());
    memcpy(req.data(), request.data(), request.size());

    bool rc = false;
    auto sendStart = std::chrono::high_resolution_clock::now();
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
            auto recvStart = std::chrono::high_resolution_clock::now();
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
                            buffer(static_cast<const char *>(response.data()),
                                   static_cast<const char *>(response.data()) + response.size());
                    std::string res;
                    Compression::Decompress(buffer, res);
                    callback(res);
                } else {
                    if (std::chrono::duration_cast<std::chrono::seconds>(
                             std::chrono::high_resolution_clock::now() - recvStart).count() >= IPC_TIMEOUT) {
                        LOG_ERROR("Reading request's response timed out!");
                        callback(IPC_TIMED_OUT_MSG);
                        return;
                    }
                }

                boost::this_thread::restore_interruption ri(di);
                boost::this_thread::interruption_point();
            } while (!rc);
        } else {
            if (std::chrono::duration_cast<std::chrono::seconds>(
                     std::chrono::high_resolution_clock::now() - sendStart).count() >= IPC_TIMEOUT) {
                LOG_ERROR("Request timed out!");
                callback(IPC_TIMED_OUT_MSG);
                return;
            }
        }

        boost::this_thread::restore_interruption ri(di);
        boost::this_thread::interruption_point();
    } while (!rc);
}

void IPCClient::SendRequests()
{
    while (true) {
        {
            std::lock_guard<std::mutex> lock(m_workerMutex);
            (void)lock;

            if (!m_running)
                break;
        }

        bool isReqQueueEmpty;
        std::string message;
        Callback_t callback;

        {
            std::lock_guard<std::mutex> lock(m_dataMutex);
            (void)lock;

            isReqQueueEmpty = !(m_reqMessages.size() > 0);
            if (!isReqQueueEmpty) {
                message = m_reqMessages.front();
                callback = m_reqCallbacks.front();
            }
        }

        if (!isReqQueueEmpty) {
            SendARequest(message, callback);

            {
                std::lock_guard<std::mutex> lock(m_dataMutex);
                (void)lock;

                m_reqMessages.pop();
                m_reqCallbacks.pop();
            }
        }

        boost::this_thread::interruption_point();
    }
}

