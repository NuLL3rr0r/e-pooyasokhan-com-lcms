#ifndef IPCPROTOCOL_HPP
#define IPCPROTOCOL_HPP


#include <string>

namespace MyLib {
    class IPCProtocol;
}

class MyLib::IPCProtocol
{
public:
    static std::string Name();
    static std::string Version();
    static unsigned char VersionMajor();
    static unsigned char NameMinor();
};


#endif /* IPCPROTOCOL_HPP */


