#include <QApplication>
#include <QDebug>
#include <MyLib/log.hpp>
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
    LOG_INFO("Initializing application...");
}

Application::~Application()
{
    LOG_INFO("Application terminated!");
}

void Application::OnSplashScreenConnectionFailed()
{
    LOG_FATAL("Initial connection to server failed!");

    m_splashScreen->deleteLater();
    m_splashScreen.release();

    Terminate();
}

void Application::OnSplashScreenConnectionEstablished()
{
    LOG_INFO("Initial connection to server established successfully!");

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
    LOG_WARNING("Login canceled by user!");

    m_loginWindow->deleteLater();
    m_loginWindow.release();

    Terminate();
}

void Application::OnLoginSucceeded()
{
    LOG_INFO("Logged in successfully!");

    m_loginWindow->deleteLater();
    m_loginWindow.release();

    m_mainWindow = make_unique<MainWindow>(MainWindow::EUserType_Student);

    QObject::connect(m_mainWindow.get(), SIGNAL(signal_Closed()),
                     this, SLOT(OnMainWindowClosed()));

    m_mainWindow->OpenWidnow();
}

void Application::OnMainWindowClosed()
{
    LOG_INFO("User exited application!");

    m_mainWindow->deleteLater();
    m_mainWindow.release();

    Terminate();
}

void Application::Start()
{
    LOG_INFO("Starting application...");

    if (m_isInitialized)
        return;

    m_isInitialized = true;

    m_splashScreen = make_unique<SplashScreen>();

    QObject::connect(m_splashScreen.get(), SIGNAL(signal_ConnectionFailed()),
                     this, SLOT(OnSplashScreenConnectionFailed()));
    QObject::connect(m_splashScreen.get(), SIGNAL(signal_ConnectionEstablished()),
                             this, SLOT(OnSplashScreenConnectionEstablished()));

    m_splashScreen->showNormal();

    // tempooooooooooooooooooooooo
    //m_splashScreen = make_unique<SplashScreen>();
    //OnSplashScreenConnectionEstablished();

    // tempooooooooooooooooooooooo
    //m_loginWindow = make_unique<LoginWindow>();
    //OnLoginSucceeded();
}

void Application::Terminate()
{
    LOG_INFO("Terminating application...");
    QApplication::exit(0);
}

