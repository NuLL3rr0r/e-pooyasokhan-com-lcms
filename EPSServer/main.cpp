#include <iostream>
#include <string>
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <MyLib/ipcserver.hpp>
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

#if defined (__unix__)
    int lock;
#elif defined(_WIN32)
    HANDLE lock;
#endif /* defined (__unix__) */

    if(!MyLib::System::GetLock(appId, lock)) {
        std::cerr << "Process is already running!" << std::endl;
        return EXIT_FAILURE;
    }
std::cout<<appPath<<std::endl;
    EPSServer::RT::Static->AppPath = appPath;
    EPSServer::DBTables::InitTables();

    MyLib::IPCServer server(54323);
    server.Start();

    return EXIT_SUCCESS;
}

