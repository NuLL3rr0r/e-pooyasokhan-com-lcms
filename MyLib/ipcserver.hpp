#ifndef IPCSERVER_HPP
#define IPCSERVER_HPP


#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <boost/thread/thread.hpp>
#include <zmq.hpp>
#include "log.hpp"

namespace MyLib {
    class IPCServer;
}

class MyLib::IPCServer
{
private:
    typedef std::unique_ptr<boost::thread> thread_ptr;
    typedef std::unique_ptr<zmq::context_t> context_ptr;
    typedef std::unique_ptr<zmq::socket_t> socket_ptr;

    typedef unsigned short int port_t;

private:
    bool m_running;
    port_t m_port;

    thread_ptr m_workerThread;
    std::mutex m_workerMutex;

    context_ptr m_context;
    socket_ptr m_socket;

public:
    IPCServer();
    IPCServer(port_t port);
    ~IPCServer();

public:
    port_t GetPort();

    void SetPort(port_t port);

    bool IsRunning();
    void Start();
    void Stop();

private:
    void Listen();

    template<typename _IPCReponseT>
    void SendResponse(const _IPCReponseT &response)
    {
        zmq::message_t res(response.Buffer().size());
        memcpy(response.Buffer().data(), response.Buffer().data(), response.Buffer().size());

        try {
            std::lock_guard<std::mutex> lock(m_workerMutex);
            (void)lock;

            m_socket->send(res, ZMQ_NOBLOCK);
        } catch (...){
            LOG_ERROR("...");
        }
    }
};


#endif /* IPCSERVER_HPP */


