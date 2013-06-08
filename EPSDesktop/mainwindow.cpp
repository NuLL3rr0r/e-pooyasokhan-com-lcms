#include <QApplication>
#include <QMessageBox>
#include <QQmlContext>
#include <QQuickItem>
#include <QScreen>
#include "mainwindow.hpp"

using namespace EPSDesktop;

MainWindow::MainWindow(const EUserType &userType, QWindow *parent)
    : QQuickView(parent)
{
    QString windowTitle;

    switch (userType) {
    case EUserType_God:
        // Fall through
    case EUserType_Admin:
        windowTitle = "Admin Version";
        break;
    case EUserType_Teacher:
        windowTitle = "Teacher Version";
        break;
    case EUserType_Student:
        // Fall through
    default:
        windowTitle = "Student Version";
        break;
    }

    this->setTitle(windowTitle);

    this->setFlags( Qt::Window | Qt::MSWindowsFixedSizeDialogHint
                   | Qt::WindowTitleHint );

    this->rootContext()->setContextProperty("cppMainWindow", this);

    this->setSource(QUrl("qrc:/mainwindow.qml"));

    QSize screenSize = QApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);

    QObject *rootObject = this->rootObject();
    QObject::connect(rootObject, SIGNAL(signal_closed()),
                     this, SLOT(OnClosed()));

    QObject::connect(this, SIGNAL(signal_XChanged(int)),
                     this, SLOT(OnXChanged(int)));
    QObject::connect(this, SIGNAL(signal_YChanged(int)),
                     this, SLOT(OnYChanged(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::OnClosed()
{
    this->close();
    emit signal_Closed();
}


void MainWindow::OnXChanged(int x)
{
    this->setX(x);
}

void MainWindow::OnYChanged(int y)
{
    this->setY(y);
}

int MainWindow::GetX() const
{
    return this->x();
}

void MainWindow::SetX(int x)
{
    emit signal_XChanged(x);
}

int MainWindow::GetY() const
{
    return this->y();
}

void MainWindow::SetY(int y)
{
    emit signal_YChanged(y);
}

void MainWindow::OpenWidnow()
{
    this->showNormal();
    emit signal_Shown();
}

