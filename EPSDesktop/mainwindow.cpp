#include <QApplication>
#include <QMessageBox>
#include <QQmlContext>
#include <QQuickItem>
#include <QScreen>
#include "mainwindow.hpp"
#include "splashscreen.hpp"

using namespace EPSDesktop;

MainWindow::MainWindow(QWindow *parent)
    : QQuickView(parent)
{
    this->setFlags(Qt::Window);

    this->rootContext()->setContextProperty("cppMainWindow", this);

    this->setSource(QUrl("qrc:/mainwindow.qml"));

    QSize screenSize = QApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);
}

MainWindow::~MainWindow()
{

}



