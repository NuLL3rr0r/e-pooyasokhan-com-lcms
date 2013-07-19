#ifndef RT_HPP
#define RT_HPP


#include <memory>
#include <mutex>

namespace MyLib {
    class IPCClient;
}

namespace EPSDesktop {
    class RT;
}

class EPSDesktop::RT
{
private:
    struct StorageStruct
    {
        std::string IPAddress;
    };

    typedef std::unique_ptr<StorageStruct> Storage_ptr;
    typedef std::unique_ptr<MyLib::IPCClient> IPCClient_ptr;

private:
    static std::mutex m_storageMutex;
    static Storage_ptr m_storageInstance;

    static std::mutex m_ipcClientMutex;
    static IPCClient_ptr m_ipcClientInstance;

public:
    static StorageStruct *Storage();
    static MyLib::IPCClient *IPC();
};


#endif /* RT_HPP */


