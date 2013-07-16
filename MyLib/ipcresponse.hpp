#ifndef IPCRESPONSE_HPP
#define IPCRESPONSE_HPP


#include <functional>
#include <string>
#include <unordered_map>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "ipcprotocol.hpp"

namespace MyLib {
    class IPCResponse;
}

class MyLib::IPCResponse
{
public:
    /*IPCResponse(const Response &response, const Args_t &args = Args_t())
    {
        boost::property_tree::ptree resTree;
        resTree.put("response.protocol.name", IPCProtocol::Name());
        resTree.put("response.protocol.version", IPCProtocol::Version());
        resTree.put("response.status", ResponseToString.at(response));
        for (auto &arg : args) {
            resTree.put("response.args.key", arg.first);
            resTree.put("response.args.value", arg.second);
        }

        std::stringstream resStream;
        boost::property_tree::write_json(resStream, resTree);
        std::string resJSON(resStream.str());
    }

    ~IPCResponse()
    {

    }

public:
    void Send(const std::function<void(void)> &callback = nullptr)
    {

    }*/
};


#endif /* IPCRESPONSE_HPP */


