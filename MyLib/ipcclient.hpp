#ifndef IPCCLIENT_HPP
#define IPCCLIENT_HPP


#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <boost/thread/thread.hpp>
#include <zmq.hpp>

namespace MyLib {
    class IPCClient;
}

class MyLib::IPCClient
{
private:
    typedef std::unique_ptr<boost::thread> thread_ptr;
    typedef std::unique_ptr<zmq::context_t> context_ptr;
    typedef std::unique_ptr<zmq::socket_t> socket_ptr;

    typedef unsigned short int port_t;

public:
    std::function<void(const std::string &)> OnMessageSent;

private:
    std::string m_id;
    bool m_running;

    std::string m_remoteHost;
    port_t m_remotePort;

    std::queue<std::string> m_requests;

    thread_ptr m_workerThread;
    std::mutex m_workerMutex;
    std::mutex m_dataMutex;

    context_ptr m_context;
    socket_ptr m_socket;

public:
    IPCClient();
    IPCClient(const std::string &id, const std::string &remoteHost, port_t remotePort);
    ~IPCClient();

public:
    std::string GetId() const;
    std::string GetRemoteHost() const;
    port_t GetRemotePort() const;

    void SetId(const std::string &id);
    void SetRemoteHost(const std::string &remoteHost);
    void SetRemotePort(port_t remotePort);

    bool IsRunning() const;
    void Start();
    void Stop();

    void SendMessage(const std::string &message);

private:
    std::string GetMessage(const zmq::message_t &message);
    void SendRequest(const std::string &request);
    void SendRequests();
};


#endif /* IPCCLIENT_HPP */


