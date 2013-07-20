#include <cassert>

#if defined ( _WIN32 )
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "ipcserver.hpp"
#include "compression.hpp"
#include "exception.hpp"
#include "ipcprotocol.hpp"
#include "ipcresponse.hpp"
#include "log.hpp"
#include "make_unique.hpp"

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
    m_workerMutex.lock();
    if (m_running) {
        m_workerMutex.unlock();
        Stop();
    } else {
        m_workerMutex.unlock();
    }
}

IPCServer::port_t IPCServer::GetPort()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    return m_port;
}

void IPCServer::SetPort(port_t port)
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    if (m_running)
        return;

    m_port = port;
}

bool IPCServer::IsRunning()
{
    std::lock_guard<std::mutex> lock(m_workerMutex);
    (void)lock;

    return m_running;
}

void IPCServer::Start()
{
    LOG_INFO("Starting IPC server...");

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
        LOG_ERROR(ex.what());
        throw MyLib::Exception((boost::format("Cannot listen on port '%1%': '%2%'")
                                % boost::lexical_cast<std::string>(m_port)
                                % ex.what()).str().c_str());
    }
    catch(...) {
        LOG_ERROR("...");
        throw MyLib::Exception((boost::format("Cannot listen on port %1% !!")
                                % boost::lexical_cast<std::string>(m_port)).str().c_str());
    }

    m_running = true;

    m_workerThread = std::make_unique<boost::thread>(&IPCServer::Listen, this);
    m_workerThread->detach();
}

void IPCServer::Stop()
{
    LOG_INFO("Stopping IPC server...");

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
        LOG_ERROR("...");
    }

    m_workerThread.reset();
    m_socket.reset();
    m_context.reset();

    LOG_INFO("IPC server stopped successfully!");
}

void IPCServer::Listen()
{
    LOG_INFO("Listening on port "
             + boost::lexical_cast<std::string>(IPC_REMOTE_PORT)
             +  " for incoming IPC requests...");
    LOG_INFO("IPC server started successfully!");
    bool rc;
    while (true) {
        {
            std::lock_guard<std::mutex> lock(m_workerMutex);
            (void)lock;

            if (!m_running)
                break;
        }
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
                boost::property_tree::ptree reqTree;
                IPCProtocol::GetMessage(std::string(static_cast<const char *>(
                                                        request.data()), request.size()),
                                        reqTree);

                if (reqTree.get<std::string>("request.protocol.name") == IPCProtocol::Name()) {
                    IPCProtocol::Version_t versionMajor = boost::lexical_cast<IPCProtocol::Version_t>(
                                reqTree.get<std::string>("request.protocol.version.major"));
                    if (versionMajor == IPCProtocol::VersionMajor()) {
                        IPCProtocol::Version_t versionMinor = boost::lexical_cast<IPCProtocol::Version_t>(
                                    reqTree.get<std::string>("request.protocol.version.minor"));
                        if (versionMinor == IPCProtocol::VersionMinor()) {
                            if (!ResponseHandler.empty()) {
                                std::string response;
                                ResponseHandler(reqTree, response);
                                SendResponse(response);
                            } else {
                                IPCResponse::Common response(MyLib::IPCProtocol::ResponseStatus::Common::OK,
                                                             MyLib::IPCProtocol::CommonResponseStatusToString,
                                                             MyLib::IPCProtocol::ResponseArg::CommonHash_t {  },
                                                             MyLib::IPCProtocol::CommonResponseArgToString);
                                SendResponse(response.Message());
                            }
                        } else if (versionMinor < IPCProtocol::VersionMinor()) {
                            IPCResponse::Common response(MyLib::IPCProtocol::ResponseStatus::Common::ExpiredProtocolVersion,
                                                         MyLib::IPCProtocol::CommonResponseStatusToString,
                                                         MyLib::IPCProtocol::ResponseArg::CommonHash_t {  },
                                                         MyLib::IPCProtocol::CommonResponseArgToString);
                            SendResponse(response.Message());
                        } else {
                            IPCResponse::Common response(MyLib::IPCProtocol::ResponseStatus::Common::InvalidProtocolVersion,
                                                         MyLib::IPCProtocol::CommonResponseStatusToString,
                                                         MyLib::IPCProtocol::ResponseArg::CommonHash_t {  },
                                                         MyLib::IPCProtocol::CommonResponseArgToString);
                            SendResponse(response.Message());
                        }
                    } else if (versionMajor < IPCProtocol::VersionMajor()) {
                        IPCResponse::Common response(MyLib::IPCProtocol::ResponseStatus::Common::ExpiredProtocolVersion,
                                                     MyLib::IPCProtocol::CommonResponseStatusToString,
                                                     MyLib::IPCProtocol::ResponseArg::CommonHash_t {  },
                                                     MyLib::IPCProtocol::CommonResponseArgToString);
                        SendResponse(response.Message());
                    } else {
                        IPCResponse::Common response(MyLib::IPCProtocol::ResponseStatus::Common::InvalidProtocolVersion,
                                                     MyLib::IPCProtocol::CommonResponseStatusToString,
                                                     MyLib::IPCProtocol::ResponseArg::CommonHash_t {  },
                                                     MyLib::IPCProtocol::CommonResponseArgToString);
                        SendResponse(response.Message());
                    }
                } else {
                    IPCResponse::Common response(MyLib::IPCProtocol::ResponseStatus::Common::InvalidProtocol,
                                                 MyLib::IPCProtocol::CommonResponseStatusToString,
                                                 MyLib::IPCProtocol::ResponseArg::CommonHash_t {  },
                                                 MyLib::IPCProtocol::CommonResponseArgToString);
                    SendResponse(response.Message());
                }
            }

            catch (...) {
                IPCResponse::Common response(MyLib::IPCProtocol::ResponseStatus::Common::InvalidProtocol,
                                             MyLib::IPCProtocol::CommonResponseStatusToString,
                                             MyLib::IPCProtocol::ResponseArg::CommonHash_t {  },
                                             MyLib::IPCProtocol::CommonResponseArgToString);
                SendResponse(response.Message());
            }
        }

        boost::this_thread::restore_interruption ri(di);
        boost::this_thread::interruption_point();
    }
}

void IPCServer::SendResponse(const std::string &response)
{
    zmq::message_t res(response.size());
    memcpy(res.data(), response.data(), response.size());

    try {
        std::lock_guard<std::mutex> lock(m_workerMutex);
        (void)lock;

        m_socket->send(res, ZMQ_NOBLOCK);
    } catch (...){
    }

}

