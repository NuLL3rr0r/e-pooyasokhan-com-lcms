#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP


#include <QQuickView>

namespace EPSDesktop {
    class LoginWindow;
}

class EPSDesktop::LoginWindow : public QQuickView
{
    Q_OBJECT

    Q_PROPERTY( int X READ GetX WRITE SetX NOTIFY signal_XChanged )
    Q_PROPERTY( int Y READ GetY WRITE SetY NOTIFY signal_YChanged )

public:
    LoginWindow(QWindow *parent = 0);
    ~LoginWindow();

signals:
    void signal_Shown();
    void signal_XChanged(int);
    void signal_YChanged(int);

private slots:
    void OnXChanged(int x);
    void OnYChanged(int y);

public:
    int GetX() const;
    void SetX(int x);

    int GetY() const;
    void SetY(int y);

public:
    void OpenWidnow();

private:

};


#endif /* LOGINWINDOW_HPP */


