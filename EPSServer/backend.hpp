#ifndef BACKEND_HPP
#define BACKEND_HPP


#include <boost/property_tree/ptree.hpp>
#include <MyLib/compression.hpp>

namespace MyLib {
}

namespace EPSServer {
    class Backend;
}

class EPSServer::Backend
{
public:
    void OnIPCRequestReceived(const boost::property_tree::ptree &requestTree,
                              MyLib::Compression::CompressionBuffer_t &out_responseBuffer);

    void HandShake(const boost::property_tree::ptree &requestTree,
                   MyLib::Compression::CompressionBuffer_t &out_responseBuffer);

    void LatestDesktopClientVersion(const boost::property_tree::ptree &requestTree,
                                    MyLib::Compression::CompressionBuffer_t &out_responseBuffer);
};


#endif /* BACKEND_HPP */


