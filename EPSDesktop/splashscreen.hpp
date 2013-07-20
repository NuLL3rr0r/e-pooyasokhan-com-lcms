#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP


#include <memory>
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
    std::unique_ptr<QNetworkAccessManager> m_networkAccessManager;

private:
    bool m_connectionFailed;

public:
    SplashScreen(QWindow *parent = 0);
    ~SplashScreen();

signals:
    void signal_Closing();
    void signal_ConnectionFailed();
    void signal_ConnectionEstablished();

    void Signal_OnHandShakeResponded(const std::string &response);

private slots:
    void OnSplashScreenPoppedUp();
    void OnSplashScreenTimedOut();

    void OnConnectionEstablished(QNetworkReply *reply);

    void OnHandShakeResponded(const std::string &response);

private:
    void OnHandShakeResponded_(const std::string &response);

private:
    void TryConnection();
    void TryHandShake();
};


#endif /* SPLASHSCREEN_HPP */


