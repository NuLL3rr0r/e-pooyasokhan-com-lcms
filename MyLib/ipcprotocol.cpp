#include "ipcprotocol.hpp"

using namespace std;
using namespace  MyLib;

std::string IPCProtocol::Name()
{
    return IPC_PROTOCOL_NAME;
}

std::string IPCProtocol::Version()
{
    return IPC_PROTOCOL_VERSION;
}

unsigned char IPCProtocol::VersionMajor()
{
    return IPC_PROTOCOL_VERSION_MAJOR;
}

unsigned char IPCProtocol::NameMinor()
{
    return IPC_PROTOCOL_VERSION_MINOR;
}

