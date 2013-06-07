#include <iostream>
#include <string>
#include <cstdlib>

#if defined ( _WIN32 )
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <MyLib/ipcserver.hpp>
#include <MyLib/make_unique.hpp>
#include <MyLib/mylib.hpp>
#include <MyLib/system.hpp>
#include "dbtables.hpp"
#include "rt.hpp"

int main(int argc, char **argv)
{
    boost::filesystem::path path(boost::filesystem::initial_path<boost::filesystem::path>());
    if (argc > 0 && argv[0] != NULL)
        path = boost::filesystem::system_complete(boost::filesystem::path(argv[0]));
    std::string appId(path.filename().string());
    std::string appPath(boost::algorithm::replace_last_copy(path.string(), appId, ""));
    boost::filesystem::current_path(appPath);
    MyLib::MyLibInitialize(argc, argv);

#if defined ( __unix__ )
    int lock;
#elif defined ( _WIN32 )
    HANDLE lock;
#endif  // defined ( __unix__ )

    if(!MyLib::System::GetLock(appId, lock)) {
        std::cerr << "Process is already running!" << std::endl;
        return EXIT_FAILURE;
    }

    EPSServer::RT::Storage()->AppPath = appPath;
    EPSServer::DBTables::InitTables();

    std::unique_ptr<MyLib::IPCServer> server =
            std::make_unique<MyLib::IPCServer>(11011);
    server->Start();

    while (true) {
#if defined ( _WIN32 )
        Sleep(1);
#else
        sleep(1);
#endif
    }

    return EXIT_SUCCESS;
}

