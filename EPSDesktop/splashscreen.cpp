#include <QGuiApplication>
#include <QQuickItem>
#include <QScreen>
#include "splashscreen.hpp"

using namespace EPSDesktop;

SplashScreen::SplashScreen(QWindow *parent)
    : QQuickView(parent)
{
    this->setSource(QUrl("qrc:/splashscreen.qml"));

    this->setFlags(Qt::FramelessWindowHint);
    QSize screenSize = QGuiApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);

    QObject *rootObject = this->rootObject();
    QObject::connect(rootObject, SIGNAL(signal_SplashScreenShown()),
                     this, SLOT(OnSplashScreenPoppedUp()));
    QObject::connect(rootObject, SIGNAL(signal_SplashScreenTimedOut()),
                     this, SLOT(OnSplashScreenTimedOut()));

    this->show();
}

SplashScreen::~SplashScreen()
{

}

void SplashScreen::OnSplashScreenPoppedUp()
{
    this->close();
    QGuiApplication::exit();
}

void SplashScreen::OnSplashScreenTimedOut()
{
    this->close();
    QGuiApplication::exit();
}

