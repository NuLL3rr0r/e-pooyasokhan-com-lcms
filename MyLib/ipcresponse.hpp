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
    template<typename _HashT, typename _StatusT, typename _ArgsT, typename _ArgsToStringT>
    class IPCResponse;
}

template<typename _HashT, typename _StatusT, typename _ArgsT, typename _ArgsToStringT>
class MyLib::IPCResponse
{
public:
    typedef std::unordered_map<_ArgsT, std::string> Args_t;

private:
    Compression::CompressionBuffer_t m_buffer;

public:
    IPCResponse(const _HashT hash, const _StatusT &status, const Args_t &args = Args_t(),
                const _ArgsToStringT &argsToStringT = _ArgsToStringT())
    {
        boost::property_tree::ptree resTree;
        resTree.put("response.protocol.name", IPCProtocol::Name());
        resTree.put("response.protocol.version", IPCProtocol::Version());
        resTree.put("response.status", hash.at(status));
        for (auto &arg : args) {
            resTree.put("response.args.key", argsToStringT.at(arg.first));
            resTree.put("response.args.value", arg.second);
        }

        std::stringstream resStream;
        boost::property_tree::write_json(resStream, resTree);
        std::string resJSON(resStream.str());

        Compression::Compress(resJSON, m_buffer);
    }

public:
    const Compression::CompressionBuffer_t &Buffer() const
    {
        return m_buffer;
    }
};


#endif /* IPCRESPONSE_HPP */


