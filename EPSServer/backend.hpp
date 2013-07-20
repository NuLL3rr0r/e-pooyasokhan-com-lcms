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
                              std::string &out_response);

    void HandShake(const boost::property_tree::ptree &requestTree,
                   std::string &out_response);

    void LatestDesktopClientVersion(const boost::property_tree::ptree &requestTree,
                                    std::string &out_response);
};


#endif /* BACKEND_HPP */


