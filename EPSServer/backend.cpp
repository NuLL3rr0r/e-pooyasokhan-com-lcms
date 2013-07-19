#include <string>
#include <MyLib/ipcprotocol.hpp>
#include <MyLib/ipcresponse.hpp>
#include <MyLib/log.hpp>
#include "backend.hpp"

using namespace std;
using namespace boost;
using namespace MyLib;
using namespace EPSServer;

void Backend::OnIPCRequestReceived(const boost::property_tree::ptree &requestTree,
                                   MyLib::Compression::CompressionBuffer_t &out_responseBuffer)
{
    IPCProtocol::Request req(IPCProtocol::RequestToEnum.at(requestTree.get<std::string>("request.topic")));
    out_responseBuffer.clear();

    switch (req) {
    case IPCProtocol::Request::HandShake:
        HandShake(requestTree, out_responseBuffer);
        break;
    case IPCProtocol::Request::LatestDesktopClientVersion:
        LatestDesktopClientVersion(requestTree, out_responseBuffer);
        break;
    default:
        break;
    }
}

void Backend::HandShake(const boost::property_tree::ptree &requestTree,
                        MyLib::Compression::CompressionBuffer_t &out_responseBuffer)
{
    LOG_INFO("Hand shake from ");
    IPCResponse::HandShake response(MyLib::IPCProtocol::ResponseStatus::Common::OK,
                                    MyLib::IPCProtocol::CommonResponseStatusToString,
                                    MyLib::IPCProtocol::ResponseArg::CommonHash_t {  },
                                    MyLib::IPCProtocol::CommonResponseArgToString);
    out_responseBuffer = response.Buffer();
}

void Backend::LatestDesktopClientVersion(const boost::property_tree::ptree &requestTree,
                                         MyLib::Compression::CompressionBuffer_t &out_responseBuffer)
{

}



