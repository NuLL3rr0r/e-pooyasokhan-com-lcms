#include <boost/filesystem.hpp>
#include "mylib.hpp"

#if defined ( _WIN32 )

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#endif  // defined ( _WIN32 )

void MyLib::MyLibInitialize(const std::string &path)
{
    boost::filesystem::current_path(path);
}

