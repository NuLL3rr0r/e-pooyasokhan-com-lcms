#if defined ( __unix__ )
#include <fcntl.h>
#endif  // defined ( __unix__ )

#include "system.hpp"

using namespace std;
using namespace MyLib;

#if defined ( __unix__ )
const mode_t System::LOCK_FILE_PERMISSION = 0666;
#endif  // defined ( __unix__ )

#if defined ( __unix__ )

bool System::GetLock(const std::string &name, int &out_handle)
{
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 1;

    if ((out_handle = open((name + ".lock").c_str(), O_WRONLY | O_CREAT, LOCK_FILE_PERMISSION)) == -1)
        return false;

    if (fcntl(out_handle, F_SETLK, &fl) == -1)
        return false;

    return true;
}

void System::ReleaseLock(int &handle)
{
    close(handle);
}

#elif defined ( _WIN32 )

bool System::GetLock(const std::string &name, HANDLE &out_handle)
{
    try {
        out_handle = OpenMutex(MUTEX_ALL_ACCESS, TRUE, name.c_str());
        if (!out_handle) {
            out_handle = CreateMutex(NULL, TRUE, name.c_str());
            return true;
        }
    } catch (...) {
    }

    return false;
}

void System::ReleaseLock(HANDLE &handle)
{
    ReleaseMutex(handle);
    CloseHandle(handle);
}

#endif  // defined ( __unix__ )


