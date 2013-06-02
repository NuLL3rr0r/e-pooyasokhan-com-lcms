#if defined ( _WIN32 )
#include <windows.h>
#endif  // defined ( _WIN32 )

#include <QApplication>
#include <QMessageBox>
#include <QQuickItem>
#include <QScreen>
#include "splashscreen.hpp"
#include <dwmapi.h>

using namespace EPSDesktop;

SplashScreen::SplashScreen(QWindow *parent)
    : QQuickView(parent)
{
    // Shoud have NULL value, otherwise we crash
    m_networkAccessManager = NULL;

    // Add Qt::X11BypassWindowManagerHint for X11 if Qt::WindowStaysOnTopHint won't work
    // Also this is an elegant solution for toggling stay-on-top on windows if necessary
    // SetWindowPos(this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    this->setFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    /****** NOT WORKING RIGHT NOW
    // TranslucentBackground
    this->setSurfaceType(QSurface::OpenGLSurface);
    QSurfaceFormat surfaceFormat;
    surfaceFormat.setAlphaBufferSize(8);
    surfaceFormat.setRenderableType(QSurfaceFormat::OpenGL);
    this->setFormat(surfaceFormat);
    //QColor color;
    //color.setRedF(0.0);
    //color.setGreenF(0.0);
    //color.setBlueF(0.0);
    //color.setAlphaF(0.0);
    //this->setColor(color);
    this->setColor(Qt::transparent);
    this->setClearBeforeRendering(true);
    *****************/

    this->setSource(QUrl("qrc:/splashscreen.qml"));

    // Centering the splash
    QSize screenSize = QApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);

    // Connecting signals/slots
    QObject *rootObject = this->rootObject();
    QObject::connect(rootObject, SIGNAL(signal_SplashScreenPoppedUp()),
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
    TryConnection();
}

void SplashScreen::OnSplashScreenTimedOut()
{
    //this->close();
    //QGuiApplication::exit();
}

void SplashScreen::OnConnectionEstablished(QNetworkReply *reply)
{
    QString ipAddress;

    if(reply->error() == QNetworkReply::NoError) {
        ipAddress = reply->readAll();

        QMessageBox *messageBox = new QMessageBox(QMessageBox::Information, "IP", ipAddress,
                                                  QMessageBox::Ok, NULL,
                                                  Qt::Dialog
                                                  | Qt::MSWindowsFixedSizeDialogHint
                                                  | Qt::WindowStaysOnTopHint);
        messageBox->setAttribute(Qt::WA_DeleteOnClose, true);
        messageBox->setAttribute(Qt::WA_RightToLeft, true);
        messageBox->setModal(true);
        messageBox->exec();
    } else {
        QMessageBox *messageBox = new QMessageBox(QMessageBox::Critical, "خطا در برقراری ارتباط",
                                                  "متاسفانه امکان دسترسی به سرور برنامه وجود ندارد.",
                                                  QMessageBox::Retry | QMessageBox::Cancel, NULL,
                                                  Qt::Dialog
                                                  | Qt::MSWindowsFixedSizeDialogHint
                                                  | Qt::WindowStaysOnTopHint);
        messageBox->setAttribute(Qt::WA_DeleteOnClose, false);
        messageBox->setAttribute(Qt::WA_RightToLeft, true);
        messageBox->setModal(true);
        messageBox->exec();

        if (messageBox->result() == QMessageBox::Retry) {
            messageBox->deleteLater();
            reply->deleteLater();
            TryConnection();
            return;
        } else {
            QGuiApplication::exit();
        }
    }

    reply->deleteLater();
}

void SplashScreen::TryConnection()
{
    // we should delete it before new allocation to avoid leaks
    if (m_networkAccessManager != NULL)
        m_networkAccessManager->deleteLater();

    QNetworkConfigurationManager *configurationManager = new QNetworkConfigurationManager();

    if(!configurationManager->isOnline())
    {
        QMessageBox *messageBox = new QMessageBox(QMessageBox::Critical, "خطا در برقراری ارتباط",
                                                  "جهت ورود به نرم افزار به ارتباط اینترنت نیازمندید.",
                                                  QMessageBox::Retry | QMessageBox::Cancel, NULL,
                                                  Qt::Dialog
                                                  | Qt::MSWindowsFixedSizeDialogHint
                                                  | Qt::WindowStaysOnTopHint);
        messageBox->setAttribute(Qt::WA_DeleteOnClose, false);
        messageBox->setAttribute(Qt::WA_RightToLeft, true);
        messageBox->setModal(true);
        messageBox->exec();

        if (messageBox->result() == QMessageBox::Retry) {
            messageBox->deleteLater();
            configurationManager->deleteLater();
            TryConnection();
            return;
        } else {
            QGuiApplication::exit();
        }
    }

    configurationManager->deleteLater();

    m_networkAccessManager = new QNetworkAccessManager();
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply *)),
            SLOT(OnConnectionEstablished(QNetworkReply *)));
    m_networkAccessManager->get(QNetworkRequest(QUrl("http://client.e-pooyasokhan.com/ip.php")));
}

