#ifndef _WIN32
#include <iostream>
#endif  // _WIN32

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <QApplication>
#include <QMessageBox>
#include <QWidget>
#include <MyLib/mylib.hpp>
#include <MyLib/system.hpp>

int main(int argc, char **argv)
{
    boost::filesystem::path path(boost::filesystem::initial_path<boost::filesystem::path>());
    if (argc > 0 && argv[0] != NULL)
        path = boost::filesystem::system_complete(boost::filesystem::path(argv[0]));
    std::string appId(path.filename().string());
    std::string appPath(boost::algorithm::replace_last_copy(path.string(), appId, ""));
    boost::filesystem::current_path(appPath);
    MyLib::MyLibInitialize(appPath);

#if defined ( __unix__ )
    int lock;
#elif defined ( _WIN32 )
    HANDLE lock;
#endif  // defined ( __unix__ )

    if(!MyLib::System::GetLock(appId, lock)) {
    #if defined ( _WIN32 )
        MessageBox(NULL, "Process is already running!", "Error", MB_OK);
    #else
        std::cerr << "Process is already running!" << std::endl;
    #endif  // defined ( _WIN32 )
        return EXIT_FAILURE;
    }


    QApplication a(argc, argv);
    QWidget w;
    w.resize(550, 400);
    w.show();

    return a.exec();
}

