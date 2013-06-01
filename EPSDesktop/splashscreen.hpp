#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP


#include <string>
#include <QQuickView>

namespace EPSDesktop {
    class SplashScreen;
}

class EPSDesktop::SplashScreen : public QQuickView
{
    Q_OBJECT

public:
    SplashScreen(QWindow *parent = 0);
    ~SplashScreen();

public slots:
    void OnSplashScreenPoppedUp();
    void OnSplashScreenTimedOut();
};


#endif /* SPLASHSCREEN_HPP */


