#ifndef IPCREQUEST_HPP
#define IPCREQUEST_HPP


#include <string>
#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "compression.hpp"
#include "ipcprotocol.hpp"

namespace MyLib {
    template<typename _RequestArgT, typename _RequestArgToStringT>
    class BasicIPCRequest;

    class IPCRequest;
}

class MyLib::IPCRequest {
public:
    typedef MyLib::BasicIPCRequest<MyLib::IPCProtocol::RequestArg::HandShakeHash_t,
    MyLib::IPCProtocol::RequestArg::HandShakeToString_t> HandShake;
};

template<typename _RequestArgHashT, typename _RequestArgToStringT>
class MyLib::BasicIPCRequest
{
private:
    Compression::CompressionBuffer_t m_buffer;

public:
    BasicIPCRequest(const IPCProtocol::Request &request,
                    const _RequestArgHashT &args = _RequestArgHashT(),
                    const _RequestArgToStringT &argsToStringT = _RequestArgToStringT())
    {
        try {
            boost::property_tree::ptree reqTree;
            reqTree.put("request.protocol.name", IPCProtocol::Name());
            reqTree.put("request.protocol.version.major",
                        boost::lexical_cast<std::string>(IPCProtocol::VersionMajor()));
            reqTree.put("request.protocol.version.minor",
                        boost::lexical_cast<std::string>(IPCProtocol::VersionMinor()));
            reqTree.put("request.client.id", "");
            reqTree.put("request.topic", IPCProtocol::RequestToString.at(request));
            for (const auto &arg : args) {
                reqTree.put("request.args.key", argsToStringT.at(arg.first));
                reqTree.put("request.args.value", arg.second);
            }

            std::stringstream reqStream;
            boost::property_tree::write_json(reqStream, reqTree);
            std::string reqJSON(reqStream.str());

            Compression::Compress(reqJSON, m_buffer);
        } catch (...) {

        }
    }

public:
    const Compression::CompressionBuffer_t &Buffer() const
    {
        return m_buffer;
    }
};


#endif /* IPCREQUEST_HPP */


