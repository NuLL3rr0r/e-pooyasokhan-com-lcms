#include <QApplication>
#include <QMessageBox>
#include <QQmlContext>
#include <QQuickItem>
#include <QScreen>
#include "loginwindow.hpp"

using namespace EPSDesktop;

LoginWindow::LoginWindow(QWindow *parent)
    : QQuickView(parent)
{
    this->setTitle("ورود");

    this->setFlags(Qt::Window);

    this->rootContext()->setContextProperty("cppLoginWindow", this);

    this->setSource(QUrl("qrc:/loginwindow.qml"));

    QSize screenSize = QApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);
}

LoginWindow::~LoginWindow()
{

}


