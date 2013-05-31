#include <QGuiApplication>
#include <QScreen>
#include "splashscreen.hpp"

using namespace EPS;

SplashScreen::SplashScreen(QWindow *parent)
    : QQuickView(parent)
{
    this->setSource(QUrl("qrc:/splashscreen.qml"));

    this->setFlags(Qt::FramelessWindowHint);
    QSize screenSize = QGuiApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);

    this->show();
}

SplashScreen::~SplashScreen()
{

}

