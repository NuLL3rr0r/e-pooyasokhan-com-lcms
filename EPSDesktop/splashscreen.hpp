#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP


#include <string>
#include <QtNetwork>
#include <QQuickView>

namespace EPSDesktop {
    class SplashScreen;
}

class EPSDesktop::SplashScreen : public QQuickView
{
    Q_OBJECT

private:
    QNetworkAccessManager *m_networkAccessManager;

signals:
    void signal_CloseRequest();

private slots:
    void OnSplashScreenPoppedUp();
    void OnSplashScreenTimedOut();

    void OnConnectionEstablished(QNetworkReply *reply);

public:
    SplashScreen(QWindow *parent = 0);
    ~SplashScreen();

private:
    void TryConnection();
};


#endif /* SPLASHSCREEN_HPP */


