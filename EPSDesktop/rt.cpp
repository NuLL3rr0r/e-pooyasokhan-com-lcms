#include <MyLib/ipcclient.hpp>
#include <MyLib/make_unique.hpp>
#include "rt.hpp"

using namespace std;
using namespace EPSDesktop;

std::mutex RT::m_storageMutex;
RT::Storage_ptr RT::m_storageInstance;

std::mutex RT::m_ipcClientMutex;
RT::IPCClient_ptr RT::m_ipcClientInstance;

RT::StorageStruct *RT::Storage()
{
    lock_guard<mutex> lock(m_storageMutex);
    (void)lock;

    if (m_storageInstance == nullptr) {
        m_storageInstance = std::make_unique<RT::StorageStruct>();
    }

    return m_storageInstance.get();
}

MyLib::IPCClient *RT::IPC()
{
    lock_guard<mutex> lock(m_ipcClientMutex);
    (void)lock;

    if (m_ipcClientInstance == nullptr) {
        m_ipcClientInstance = std::make_unique<MyLib::IPCClient>();
    }

    return m_ipcClientInstance.get();
}

