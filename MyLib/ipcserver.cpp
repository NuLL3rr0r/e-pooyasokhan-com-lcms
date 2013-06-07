#include <cassert>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <MyLib/make_unique.hpp>
#include "ipcserver.hpp"
#include "exception.hpp"


#define     MSG_RECEIVED            "RCVD!"
#define     MSG_INVALID             "INVLD!"


using namespace MyLib;

IPCServer::IPCServer() :
    m_running(false),
    m_port(0)
{
}

IPCServer::IPCServer(port_t port) :
    m_running(false),
    m_port(port)
{
}

IPCServer::~IPCServer()
{
    if (m_running) {
        Stop();
    }
}

IPCServer::port_t IPCServer::GetPort() const
{
    return m_port;
}

void IPCServer::SetPort(port_t port)
{
    if (m_running)
        return;

    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    m_port = port;
}

bool IPCServer::IsRunning() const
{
    return m_running;
}

void IPCServer::Start()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    assert(m_port != 0);

    if (m_running) {
        return;
    }

    std::string tcpURL((boost::format("tcp://*:%1%") % boost::lexical_cast<std::string>(m_port)).str());

    try {
        m_context = std::make_unique<zmq::context_t>(1);
        m_socket = std::make_unique<zmq::socket_t>(*m_context.get(), ZMQ_REP);

        int linger = 0;
        m_socket->setsockopt(ZMQ_LINGER, &linger, sizeof(linger));

        m_socket->bind(tcpURL.c_str());
    }
    catch(const zmq::error_t &ex) {
        throw MyLib::Exception((boost::format("Cannot listen on port '%1%': '%2%'")
                                % boost::lexical_cast<std::string>(m_port)
                                % ex.what()).str().c_str());
    }
    catch(...) {
        throw MyLib::Exception((boost::format("Cannot listen on port %1% !!")
                                % boost::lexical_cast<std::string>(m_port)).str().c_str());
    }

    m_running = true;

    m_workerThread = std::make_unique<boost::thread>(&IPCServer::Listen, this);
    m_workerThread->detach();
}

void IPCServer::Stop()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    if (!m_running) {
        return;
    }

    m_running = false;
    m_workerThread->interrupt();

    std::string tcpURL((boost::format("tcp://*:%1%") % boost::lexical_cast<std::string>(m_port)).str());
    zmq_unbind((void *)m_socket.get(), tcpURL.c_str());

    try {
        m_socket->close();
        m_context->close();
    } catch(...) {
    }

    m_workerThread.reset();
    m_socket.reset();
    m_context.reset();
}

void IPCServer::Listen()
{
    bool rc;
    while(m_running) {
        boost::this_thread::disable_interruption di;

        zmq::message_t request;

        try {
            std::lock_guard<std::mutex> lock(m_workerMutex);
            (void)lock;

            rc = m_socket->recv(&request);
        } catch(...) {
            rc = false;
        }

        if (rc) {
            try {
                std::stringstream reqJSON;
                reqJSON << GetMessage(request);

                boost::property_tree::ptree reqTree;
                boost::property_tree::read_json(reqJSON, reqTree);

                if (OnMessageReceived) {
                    OnMessageReceived(reqTree.get<std::string>("req.clientId"),
                                      reqTree.get<std::string>("req.message"));
                }

                SendResponse(MSG_RECEIVED);
            }

            catch (...) {
                SendResponse(MSG_INVALID);
            }
        }

        boost::this_thread::restore_interruption ri(di);
        boost::this_thread::interruption_point();
    }
}

std::string IPCServer::GetMessage(const zmq::message_t &message)
{
    return std::string(static_cast<const char *>(message.data()), message.size());
}

bool IPCServer::SendResponse(const std::string &response)
{
    zmq::message_t msg(response.size());
    memcpy(msg.data(), response.data(), response.size());

    bool rc;

    try {
        std::lock_guard<std::mutex> lock(m_workerMutex);
        (void)lock;

        rc = m_socket->send(msg, ZMQ_NOBLOCK);
    } catch (...){
        rc = false;
    }

    return rc;
}


