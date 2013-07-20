#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include <memory>
#include <QObject>

namespace EPSDesktop {
    class Application;
    class LoginWindow;
    class MainWindow;
    class SplashScreen;
}

class EPSDesktop::Application : public QObject
{
    Q_OBJECT

private:
    bool m_isInitialized;

    std::unique_ptr<EPSDesktop::LoginWindow> m_loginWindow;
    std::unique_ptr<EPSDesktop::MainWindow> m_mainWindow;
    std::unique_ptr<EPSDesktop::SplashScreen> m_splashScreen;

public:
    explicit Application(QObject *parent = 0);
    ~Application();

signals:

private slots:
    void OnSplashScreenConnectionFailed();
    void OnSplashScreenConnectionEstablished();
    void OnLoginCanceled();
    void OnLoginSucceeded();
    void OnMainWindowClosed();

public:
    void Start();

private:
    void Terminate();
};


#endif /* APPLICATION_HPP */


