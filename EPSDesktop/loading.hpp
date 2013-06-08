#ifndef LOADING_HPP
#define LOADING_HPP


#include <mutex>
#include <QQuickView>

namespace EPSDesktop {
    class Loading;
}

class EPSDesktop::Loading : QQuickView
{
    Q_OBJECT

private:
    static std::mutex m_mutex;
    static Loading *m_instance;

public:
    static Loading *Anim();

private:
    static void Destroy();

private:
    Loading();
    ~Loading();

    Loading(Loading const &);
    Loading &operator=(Loading const &);

signals:
    void signal_Started();
    void signal_Stopped();

public:
    void Start(QWindow *parent = NULL);
    void Stop();
};


#endif /* LOADING_HPP */


