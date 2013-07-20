#ifndef IPCCLIENT_HPP
#define IPCCLIENT_HPP


#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <zmq.hpp>
#include "ipcrequest.hpp"
#include "compression.hpp"

#define     IPC_TIMED_OUT_MSG       "TIMED_OUT"

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

    typedef boost::function<void(const std::string &)> Callback_t;

private:
    bool m_running;

    std::string m_remoteHost;
    port_t m_remotePort;

    std::queue<std::string> m_reqMessages;
    std::queue<Callback_t> m_reqCallbacks;

    thread_ptr m_workerThread;
    std::mutex m_workerMutex;
    std::mutex m_dataMutex;

    context_ptr m_context;
    socket_ptr m_socket;

public:
    IPCClient();
    IPCClient(const std::string &remoteHost, port_t remotePort);
    ~IPCClient();

public:
    std::string GetRemoteHost();
    port_t GetRemotePort();

    void SetRemoteHost(const std::string &remoteHost);
    void SetRemotePort(port_t remotePort);

    bool IsRunning();
    void Start();
    void Stop();

    template<typename _IPCRequestT>
    void SendRequest(const _IPCRequestT &request, Callback_t callback)
    {
        {
            std::lock_guard<std::mutex> lock(m_workerMutex);
            (void)lock;

            if (!m_running)
                return;
        }

        std::lock_guard<std::mutex> lock(m_dataMutex);
        (void)lock;

        m_reqMessages.push(request.Message());
        m_reqCallbacks.push(callback);
    }

private:
    void SendARequest(const std::string &request, Callback_t callback);
    void SendRequests();
};


#endif /* IPCCLIENT_HPP */


