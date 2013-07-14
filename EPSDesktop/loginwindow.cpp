#include <QApplication>
#include <QMessageBox>
#include <QQmlContext>
#include <QQuickItem>
#include <QScreen>
#include <MyLib/log.hpp>
#include "loginwindow.hpp"
#include "loading.hpp"

using namespace EPSDesktop;

LoginWindow::LoginWindow(QWindow *parent)
    : QQuickView(parent),
      m_canceled(false)
{
    LOG_INFO("Initializing login window...");

    this->setTitle("ورود");

    this->setFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint
                   | Qt::WindowTitleHint);

    this->rootContext()->setContextProperty("cppLoginWindow", this);

    this->setSource(QUrl("qrc:/loginwindow.qml"));

    QSize screenSize = QApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);

    QObject *rootObject = this->rootObject();
    QObject::connect(rootObject, SIGNAL(signal_closed()),
                     this, SLOT(OnClosed()));
    QObject::connect(rootObject, SIGNAL(signal_canceled()),
                     this, SLOT(OnCanceled()));

    QObject::connect(this, SIGNAL(signal_XChanged(int)),
                     this, SLOT(OnXChanged(int)));
    QObject::connect(this, SIGNAL(signal_YChanged(int)),
                     this, SLOT(OnYChanged(int)));
}

LoginWindow::~LoginWindow()
{
    LOG_INFO("Login window closed!");
}

void LoginWindow::OnClosed()
{
    LOG_INFO("Closing login window...");

    this->close();

    if (m_canceled)
        emit signal_LoginCanceled();
}


void LoginWindow::OnCanceled()
{
    m_canceled = true;
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
    emit signal_XChanged(x);
}

int LoginWindow::GetY() const
{
    return this->y();
}

void LoginWindow::SetY(int y)
{
    emit signal_YChanged(y);
}

void LoginWindow::OpenWidnow()
{
    LOG_INFO("Opening login window...");

    this->showNormal();
    emit signal_Shown();
}

