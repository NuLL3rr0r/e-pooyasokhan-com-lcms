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

    this->setFlags( Qt::Window | Qt::MSWindowsFixedSizeDialogHint
                   | Qt::WindowTitleHint );

    this->rootContext()->setContextProperty("cppLoginWindow", this);

    this->setSource(QUrl("qrc:/loginwindow.qml"));

    QSize screenSize = QApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);

    QObject::connect(this, SIGNAL(XChanged(int)),
                     this, SLOT(OnXChanged(int)));
    QObject::connect(this, SIGNAL(YChanged(int)),
                     this, SLOT(OnYChanged(int)));
}

LoginWindow::~LoginWindow()
{

}

void LoginWindow::OnXChanged(int x)
{
    this->setX(x);
}

void LoginWindow::OnYChanged(int y)
{
    this->setY(y);
}

int LoginWindow::GetX() const
{
    return this->x();
}

void LoginWindow::SetX(int x)
{
    emit XChanged(x);
}

int LoginWindow::GetY() const
{
    return this->y();
}

void LoginWindow::SetY(int y)
{
    emit YChanged(y);
}

