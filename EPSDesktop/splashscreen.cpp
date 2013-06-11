#include <QApplication>
#include <QMessageBox>
#include <QQmlContext>
#include <QQuickItem>
#include <QScreen>
#include <MyLib/make_unique.hpp>
#include "splashscreen.hpp"

using namespace std;
using namespace EPSDesktop;

SplashScreen::SplashScreen(QWindow *parent)
    : QQuickView(parent),
      m_connectionFailed(false)
{
    this->setTitle("پویا سخن");

    this->setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->rootContext()->setContextProperty("cppSplashScreen", this);

    this->setSource(QUrl("qrc:/splashscreen.qml"));

    QSize screenSize = QApplication::primaryScreen()->size();
    this->setX((screenSize.width() - this->width()) / 2.0);
    this->setY((screenSize.height() - this->height()) / 2.0);

    QObject *rootObject = this->rootObject();
    QObject::connect(rootObject, SIGNAL(signal_splashScreenPoppedUp()),
                     this, SLOT(OnSplashScreenPoppedUp()));
    QObject::connect(rootObject, SIGNAL(signal_splashScreenTimedOut()),
                     this, SLOT(OnSplashScreenTimedOut()));
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
    this->close();

    if (!m_connectionFailed)
        emit signal_ConnectionEstablished();
    else
        emit signal_ConnectionFailed();
}

void SplashScreen::OnConnectionEstablished(QNetworkReply *reply)
{
    QString ipAddress;

    if(reply->error() == QNetworkReply::NoError) {
        ipAddress = reply->readAll();
        emit signal_Closing();
    } else {
        QMessageBox *messageBox = new QMessageBox(QMessageBox::Critical, "خطا در برقراری ارتباط",
                                                  "متاسفانه امکان دسترسی به سرور برنامه وجود ندارد.",
                                                  QMessageBox::Retry | QMessageBox::Cancel, NULL,
                                                  Qt::WindowStaysOnTopHint);
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
            m_connectionFailed = true;
            emit signal_Closing();
        }
    }

    reply->deleteLater();
}

void SplashScreen::TryConnection()
{
    if (m_networkAccessManager != nullptr) {
        m_networkAccessManager->deleteLater();
        m_networkAccessManager.release();
    }

    QNetworkConfigurationManager *configurationManager = new QNetworkConfigurationManager();

    if(!configurationManager->isOnline())
    {
        QMessageBox *messageBox = new QMessageBox(QMessageBox::Critical, "خطا در برقراری ارتباط",
                                                  "جهت ورود به نرم افزار به ارتباط اینترنت نیازمندید.",
                                                  QMessageBox::Retry | QMessageBox::Cancel, NULL,
                                                  Qt::WindowStaysOnTopHint);
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
            m_connectionFailed = true;
            emit signal_Closing();
        }
    }

    configurationManager->deleteLater();

    m_networkAccessManager = make_unique<QNetworkAccessManager>();
    connect(m_networkAccessManager.get(), SIGNAL(finished(QNetworkReply *)),
            SLOT(OnConnectionEstablished(QNetworkReply *)));
    m_networkAccessManager->get(QNetworkRequest(QUrl("http://client.e-pooyasokhan.com/ip.php")));
}

