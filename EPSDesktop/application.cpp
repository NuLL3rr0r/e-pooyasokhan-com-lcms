#include <QApplication>
#include <QDebug>
#include <MyLib/make_unique.hpp>
#include "application.hpp"
#include "loginwindow.hpp"
#include "mainwindow.hpp"
#include "splashscreen.hpp"

using namespace std;
using namespace EPSDesktop;

Application::Application(QObject *parent)
    : QObject(parent),
      m_isInitialized(false)
{
}

Application::~Application()
{
}

void Application::OnSplashScreenConnectionFailed()
{
    m_splashScreen->deleteLater();
    m_splashScreen.release();

    Terminate();
}

void Application::OnSplashScreenConnectionEstablished()
{
    m_splashScreen->deleteLater();
    m_splashScreen.release();

    m_loginWindow = make_unique<LoginWindow>();

    QObject::connect(m_loginWindow.get(), SIGNAL(signal_LoginCanceled()),
                     this, SLOT(OnLoginCanceled()));
    QObject::connect(m_loginWindow.get(), SIGNAL(signal_LoginSucceeded()),
                     this, SLOT(OnLoginSucceeded()));

    m_loginWindow->OpenWidnow();
}

void Application::OnLoginCanceled()
{
    m_loginWindow->deleteLater();
    m_loginWindow.release();

    Terminate();
}

void Application::OnLoginSucceeded()
{
    m_loginWindow->deleteLater();
    m_loginWindow.release();

    m_mainWindow = make_unique<MainWindow>(MainWindow::EUserType_Student);

    QObject::connect(m_mainWindow.get(), SIGNAL(signal_Closed()),
                     this, SLOT(OnMainWindowClosed()));

    m_mainWindow->OpenWidnow();
}

void Application::OnMainWindowClosed()
{
    /*m_mainWindow->deleteLater();
    m_mainWindow.release();

    Terminate();*/
}

void Application::Start()
{
    /*if (m_isInitialized)
        return;

    m_isInitialized = true;

    m_splashScreen = make_unique<SplashScreen>();

    QObject::connect(m_splashScreen.get(), SIGNAL(signal_ConnectionFailed()),
                     this, SLOT(OnSplashScreenConnectionFailed()));
    QObject::connect(m_splashScreen.get(), SIGNAL(signal_ConnectionEstablished()),
                             this, SLOT(OnSplashScreenConnectionEstablished()));

    m_splashScreen->showNormal();*/

    // tempooooooooooooooooooooooo
    //m_splashScreen = make_unique<SplashScreen>();
    //OnSplashScreenConnectionEstablished();

    // tempooooooooooooooooooooooo
    m_loginWindow = make_unique<LoginWindow>();
    OnLoginSucceeded();
}

void Application::Terminate()
{
    QApplication::exit(0);
}

