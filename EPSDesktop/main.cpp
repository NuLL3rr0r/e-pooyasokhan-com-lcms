#if !defined ( _WIN32 )
#include <iostream>
#endif  // !defined ( _WIN32 )

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <MyLib/mylib.hpp>
#include <MyLib/system.hpp>
#include "splashscreen.hpp"

int main(int argc, char **argv)
{
    boost::filesystem::path path(boost::filesystem::initial_path<boost::filesystem::path>());
    if (argc > 0 && argv[0] != NULL)
        path = boost::filesystem::system_complete(boost::filesystem::path(argv[0]));
    std::string appId(path.filename().string());
    std::string appPath(boost::algorithm::replace_last_copy(path.string(), appId, ""));
    boost::filesystem::current_path(appPath);
    MyLib::MyLibInitialize(argc, argv);

#if !defined ( DEBUG_BUILD )
#if defined ( __unix__ )
    int lock;
#elif defined ( _WIN32 )
    HANDLE lock;
#endif  // defined ( __unix__ )

    if(!MyLib::System::GetLock(appId, lock)) {
    #if defined ( _WIN32 )
        MessageBoxW(NULL, L"نسخه دیگری از برنامه در حال اجراست!", L"خطا",
                    MB_OK || MB_ICONERROR | MB_RTLREADING | MB_TOPMOST);
    #else
        std::cerr << "Process is already running!" << std::endl;
    #endif  // defined ( _WIN32 )
        return EXIT_FAILURE;
    }
#endif // !defined ( DEBUG_BUILD )


    QApplication app(argc, argv);

    EPSDesktop::SplashScreen *splash = new EPSDesktop::SplashScreen();
    splash->show();

    return app.exec();
}

