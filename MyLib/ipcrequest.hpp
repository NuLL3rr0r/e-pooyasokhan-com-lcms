#ifndef IPCREQUEST_HPP
#define IPCREQUEST_HPP


#include <functional>
#include <string>
#include <unordered_map>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "ipcprotocol.hpp"

namespace MyLib {
    template<typename _ArgsT>
    class IPCRequest;
}

template<typename _ArgsT>
class MyLib::IPCRequest
{
public:
    typedef std::unordered_map<_ArgsT, std::string> Args_t;

public:
    IPCRequest(const IPCProtocol::Request &request, const Args_t &args = Args_t())
    {
        boost::property_tree::ptree reqTree;
        reqTree.put("request.protocol.name", IPCProtocol::Name());
        reqTree.put("request.protocol.version", IPCProtocol::Version());
        reqTree.put("request.client.id", "");
        reqTree.put("request.topic", IPCProtocol::RequestToString.at(request));
        for (auto &arg : args) {
            reqTree.put("request.args.key", arg.first);
            reqTree.put("request.args.value", arg.second);
        }

        std::stringstream reqStream;
        boost::property_tree::write_json(reqStream, reqTree);
        std::string reqJSON(reqStream.str());
    }

    ~IPCRequest()
    {

    }

public:
    void Send(const std::function<void(void)> &callback = nullptr)
    {

    }
};


#endif /* IPCREQUEST_HPP */


