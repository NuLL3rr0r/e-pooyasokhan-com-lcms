#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include <QQuickView>

namespace EPSDesktop {
    class MainWindow;
}

class EPSDesktop::MainWindow : public QQuickView
{
    Q_OBJECT

    Q_PROPERTY( int X READ GetX WRITE SetX NOTIFY signal_XChanged )
    Q_PROPERTY( int Y READ GetY WRITE SetY NOTIFY signal_YChanged )

public:
    enum EUserType {
        EUserType_God,
        EUserType_Admin,
        EUserType_Teacher,
        EUserType_Student
    };

public:
    MainWindow(const EUserType &userType, QWindow *parent = 0);
    ~MainWindow();

signals:
    void signal_Shown();
    void signal_Closed();
    void signal_XChanged(int);
    void signal_YChanged(int);

private slots:
    void OnClosed();
    void OnXChanged(int x);
    void OnYChanged(int y);

public:
    int GetX() const;
    void SetX(int x);

    int GetY() const;
    void SetY(int y);

public:
    Q_INVOKABLE int GetScreenWidth() const;
    Q_INVOKABLE int GetScreenHeight() const;

public:
    void OpenWidnow();

private:

};


#endif /* MAINWINDOW_HPP */


