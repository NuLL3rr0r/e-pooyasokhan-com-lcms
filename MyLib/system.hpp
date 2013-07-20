#ifndef SYSTEM_HPP
#define SYSTEM_HPP


#include <string>

#if defined ( __unix__ )
#include <sys/types.h>
#elif defined ( _WIN32 )
#include <windows.h>
#include <winbase.h>    // Synchapi.h on Windows 8 and Windows Server 2012
#endif  // defined ( __unix__ )

namespace MyLib {
    class System;
}

class MyLib::System
{
private:
#if defined ( __unix__ )
    static const mode_t LOCK_FILE_PERMISSION;
#endif  // defined ( __unix__ )

public:
#if defined ( __unix__ )
    static bool GetLock(const std::string &name, int &out_handle);
    static void ReleaseLock(int &handle);
#elif defined ( _WIN32 )
    static bool GetLock(const std::string &name, HANDLE &out_handle);
    static void ReleaseLock(HANDLE &handle);
#endif  // defined ( __unix__ )
};


#endif /* SYSTEM_HPP */


