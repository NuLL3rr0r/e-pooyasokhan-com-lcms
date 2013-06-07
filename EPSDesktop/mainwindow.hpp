#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP


#include <QQuickView>

namespace EPSDesktop {
    class MainWindow;
}

class EPSDesktop::MainWindow : public QQuickView
{
    Q_OBJECT

private:

public:
    MainWindow(QWindow *parent = 0);
    ~MainWindow();

signals:

private slots:
};


#endif /* MAINWINDOW_HPP */


