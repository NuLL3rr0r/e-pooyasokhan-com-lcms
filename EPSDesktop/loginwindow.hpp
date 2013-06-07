#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP


#include <QQuickView>

namespace EPSDesktop {
    class LoginWindow;
}

class EPSDesktop::LoginWindow : public QQuickView
{
    Q_OBJECT

private:

public:
    LoginWindow(QWindow *parent = 0);
    ~LoginWindow();

signals:

private slots:

private:
};


#endif /* LOGINWINDOW_HPP */


