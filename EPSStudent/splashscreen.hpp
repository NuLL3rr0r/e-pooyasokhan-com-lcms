#ifndef SPLASHSCREEN_HPP
#define SPLASHSCREEN_HPP


#include <string>
#include <QQuickView>

namespace EPS {
    class SplashScreen;
}

class EPS::SplashScreen : public QQuickView
{
    Q_OBJECT

public:
    SplashScreen(QWindow *parent = 0);
    ~SplashScreen();
};


#endif /* SPLASHSCREEN_HPP */


