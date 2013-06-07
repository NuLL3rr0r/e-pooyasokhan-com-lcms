#ifndef IPCSERVER_HPP
#define IPCSERVER_HPP


#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <boost/thread/thread.hpp>
#include <zmq.hpp>

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

public:
    std::function<void(const std::string &, const std::string &)> OnMessageReceived;

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
    port_t GetPort() const;

    void SetPort(port_t port);

    bool IsRunning() const;
    void Start();
    void Stop();

private:
    void Listen();
    std::string GetMessage(const zmq::message_t &message);
    bool SendResponse(const std::string &response);
};


#endif /* IPCSERVER_HPP */


