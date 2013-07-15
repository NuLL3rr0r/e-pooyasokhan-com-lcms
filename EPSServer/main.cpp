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
#include <MyLib/ipcprotocol.hpp>
#include <MyLib/ipcserver.hpp>
#include <MyLib/log.hpp>
#include <MyLib/make_unique.hpp>
#include <MyLib/mylib.hpp>
#include <MyLib/system.hpp>
#include "dbtables.hpp"
#include "rt.hpp"
#include "versioninfo.hpp"

int main(int argc, char **argv)
{
    boost::filesystem::path path(boost::filesystem::initial_path<boost::filesystem::path>());
    if (argc > 0 && argv[0] != NULL)
        path = boost::filesystem::system_complete(boost::filesystem::path(argv[0]));
    std::string appId(path.filename().string());
    std::string appPath(boost::algorithm::replace_last_copy(path.string(), appId, ""));
    boost::filesystem::current_path(appPath);
    MyLib::MyLibInitialize(argc, argv);

    LOG_INFO("Version Information", "", "IPC_PROTOCOL_NAME          " + MyLib::IPCProtocol::Name(), "IPC_PROTOCOL_VERSION       " + MyLib::IPCProtocol::Version(), "BUILD_COMPILER             " VERSION_INFO_BUILD_COMPILER, "BUILD_DATE                 " VERSION_INFO_BUILD_DATE, "BUILD_HOST                 " VERSION_INFO_BUILD_HOST, "BUILD_PROCESSOR            " VERSION_INFO_BUILD_PROCESSOR, "BUILD_SYSTEM               " VERSION_INFO_BUILD_SYSTEM, "PRODUCT_COMPANY_NAME       " VERSION_INFO_PRODUCT_COMPANY_NAME, "PRODUCT_COPYRIGHT          " VERSION_INFO_PRODUCT_COPYRIGHT, "PRODUCT_DEVELOPER          " VERSION_INFO_PRODUCT_DEVELOPER, "PRODUCT_INTERNAL_NAME      " VERSION_INFO_PRODUCT_INTERNAL_NAME, "PRODUCT_NAME               " VERSION_INFO_PRODUCT_NAME, "PRODUCT_VERSION            " VERSION_INFO_PRODUCT_VERSION, "PRODUCT_DESCRIPTION        " VERSION_INFO_PRODUCT_DESCRIPTION);

#if defined ( __unix__ )
    int lock;
#elif defined ( _WIN32 )
    HANDLE lock;
#endif  // defined ( __unix__ )

    if(!MyLib::System::GetLock(appId, lock)) {
        LOG_FATAL("Process is already running!");
        return EXIT_FAILURE;
    }
    LOG_INFO("Got the process lock!");

    EPSServer::RT::Storage()->AppPath = appPath;
    EPSServer::DBTables::InitTables();

    std::unique_ptr<MyLib::IPCServer> server =
            std::make_unique<MyLib::IPCServer>(11011);
    LOG_INFO("Starting server...");
    server->Start();
    LOG_INFO("Server started successfully!");

    while (true) {
#if defined ( _WIN32 )
        Sleep(1);
#else
        sleep(1);
#endif  // defined ( _WIN32 )
    }

    return EXIT_SUCCESS;
}

