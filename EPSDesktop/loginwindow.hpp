#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP


#include <QQuickView>

namespace EPSDesktop {
    class LoginWindow;
}

class EPSDesktop::LoginWindow : public QQuickView
{
    Q_OBJECT

    Q_PROPERTY( int X READ GetX WRITE SetX NOTIFY XChanged )
    Q_PROPERTY( int Y READ GetY WRITE SetY NOTIFY YChanged )

public:
    LoginWindow(QWindow *parent = 0);
    ~LoginWindow();

signals:
    void XChanged(int);
    void YChanged(int);

private slots:
    void OnXChanged(int x);
    void OnYChanged(int y);

public:
    int GetX() const;
    void SetX(int x);

    int GetY() const;
    void SetY(int y);

private:
};


#endif /* LOGINWINDOW_HPP */


