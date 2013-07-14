#if !defined ( _WIN32 )
#include <iostream>
#endif  // !defined ( _WIN32 )

#include <memory>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <QApplication>
#include <MyLib/log.hpp>
#include <MyLib/make_unique.hpp>
#include <MyLib/mylib.hpp>
#include <MyLib/system.hpp>
#include "application.hpp"
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

    MyLib::Log::Initialize(std::cout,
                           (boost::filesystem::path(appPath) / boost::filesystem::path("logs")).string(),
                           "EPSDesktop");

#if !defined ( DEBUG_BUILD )
#if defined ( __unix__ )
    int lock;
#elif defined ( _WIN32 )
    HANDLE lock;
#endif  // defined ( __unix__ )

    if(!MyLib::System::GetLock(appId, lock)) {
        FATAL("Process is already running!");
#if defined ( _WIN32 )
        MessageBox(NULL, L"نسخه دیگری از برنامه در حال اجراست!", L"خطا",
                   MB_OK | MB_ICONERROR | MB_RTLREADING | MB_TOPMOST);
#endif  // defined ( _WIN32 )
        return EXIT_FAILURE;
    }
    LOG_INFO("Got the process lock!");
#else   // !defined ( DEBUG_BUILD )
    LOG_WARNING("Ignoring process memory-residency check!");
#endif  // !defined ( DEBUG_BUILD )

    std::unique_ptr<QApplication> app =
            std::make_unique<QApplication>(argc, argv);

    std::unique_ptr<EPSDesktop::Application> application =
            std::make_unique<EPSDesktop::Application>();
    application->Start();

    /*qDebug() << VERSION_INFO_BUILD_COMPILER;
    qDebug() << VERSION_INFO_BUILD_DATE;
    qDebug() << VERSION_INFO_BUILD_HOST;
    qDebug() << VERSION_INFO_BUILD_PROCESSOR;
    qDebug() << VERSION_INFO_BUILD_SYSTEM;
    qDebug() << VERSION_INFO_COPYRIGHT_HOLDER;
    qDebug() << VERSION_INFO_COPYRIGHT_YEAR;
    qDebug() << VERSION_INFO_DEVELOPER;
    qDebug() << VERSION_INFO_PRODUCT_NAME;
    qDebug() << VERSION_INFO_PRODUCT_VERSION;*/

    return app->exec();
}

