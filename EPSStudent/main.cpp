#ifndef _WIN32
#include <iostream>
#endif  // _WIN32

#include <boost/filesystem.hpp>
#include <QGuiApplication>
#include <QMessageBox>
#include <QQuickView>
#include <MyLib/system.hpp>

int main(int argc, char **argv)
{
    boost::filesystem::path path(boost::filesystem::initial_path<boost::filesystem::path>());
    if (argc > 0 && argv[0] != NULL)
        path = boost::filesystem::system_complete(boost::filesystem::path(argv[0]));
    std::string app_id(path.filename().string());

#if defined (__unix__)
    int lock;
#elif defined(_WIN32)
    HANDLE lock;
#endif  // defined (__unix__)

    if(!MyLib::System::GetLock(app_id, lock)) {
    #if defined(_WIN32)
        MessageBox(NULL, "Process is already running!", "Error", MB_OK);
    #else
        std::cerr << "Process is already running!" << std::endl;
    #endif  // defined(_WIN32)
        return EXIT_FAILURE;
    }


    QGuiApplication app(argc, argv);

    QQuickView *view = new QQuickView;
    view->setSource(QUrl::fromLocalFile("qml/mainwindow.qml"));
    view->show();

    return app.exec();
}

