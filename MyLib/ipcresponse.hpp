#ifndef IPCRESPONSE_HPP
#define IPCRESPONSE_HPP


#include <functional>
#include <string>
#include <unordered_map>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "compression.hpp"
#include "ipcprotocol.hpp"

namespace MyLib {
    template<typename _ResponseStatusT, typename _ResponseStatusToStringT,
             typename _ResponseArgT, typename _ResponseArgToStringT>
    class BasicIPCResponse;

    class IPCResponse;
}

class MyLib::IPCResponse {
public:
    typedef MyLib::BasicIPCResponse<MyLib::IPCProtocol::ResponseStatus::Common,
    MyLib::IPCProtocol::ResponseStatus::CommonToString_t,
    MyLib::IPCProtocol::ResponseArg::CommonHash_t,
    MyLib::IPCProtocol::ResponseArg::CommonToString_t> Common;

    typedef MyLib::BasicIPCResponse<MyLib::IPCProtocol::ResponseStatus::Common,
    MyLib::IPCProtocol::ResponseStatus::CommonToString_t,
    MyLib::IPCProtocol::ResponseArg::CommonHash_t,
    MyLib::IPCProtocol::ResponseArg::CommonToString_t> HandShake;
};

template<typename _ResponseStatusT, typename _ResponseStatusToStringT,
         typename _ResponseArgT, typename _ResponseArgToStringT>
class MyLib::BasicIPCResponse
{
private:
    std::string m_message;

public:
    BasicIPCResponse(const _ResponseStatusT status, const _ResponseStatusToStringT &statusToString,
                     const _ResponseArgT &args = _ResponseArgT(),
                     const _ResponseArgToStringT &argsToStringT = _ResponseArgToStringT())
    {
        boost::property_tree::ptree resTree;
        resTree.put("response.protocol.name", IPCProtocol::Name());
        resTree.put("response.protocol.version", IPCProtocol::Version());
        resTree.put("response.status", statusToString.at(status));
        for (auto &arg : args) {
            resTree.put("response.args.key", argsToStringT.at(arg.first));
            resTree.put("response.args.value", arg.second);
        }

        IPCProtocol::SetMessage(resTree, m_message);
    }

public:
    const std::string &Message() const
    {
        return m_message;
    }
};


#endif /* IPCRESPONSE_HPP */


