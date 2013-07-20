#include <cstdlib>
#include <QApplication>
#include <QQmlContext>
#include <QQuickItem>
#include <QScreen>
#include <QSize>
#include <MyLib/make_unique.hpp>
#include "loading.hpp"

using namespace std;
using namespace EPSDesktop;

std::mutex Loading::m_mutex;
Loading* Loading::m_instance = NULL;

Loading *Loading::Anim()
{
    lock_guard<mutex> lock(m_mutex);
    (void)lock;

    if (m_instance == NULL) {
        m_instance = new Loading();
    }

    return m_instance;
}

void Loading::Destroy()
{
    delete m_instance;
    m_instance = NULL;
}

Loading::Loading()
{
    atexit(&Loading::Destroy);

    this->setTitle("...");

    this->setFlags(Qt::Popup);
    this->setModality(Qt::ApplicationModal);

    this->rootContext()->setContextProperty("cppLoading", this);
    this->setSource(QUrl("qrc:/loading.qml"));
}

Loading::~Loading()
{
}

void Loading::Start(QWindow *parent)
{
    this->showNormal();

    if (parent) {
        this->setX((parent->width() - this->width()) / 2.0);
        this->setY((parent->height() - this->height()) / 2.0);
    } else {
        QSize screenSize = QApplication::primaryScreen()->size();
        this->setX((screenSize.width() - this->width()) / 2.0);
        this->setY((screenSize.height() - this->height()) / 2.0);
    }

    emit signal_Started();
}

void Loading::Stop()
{
    this->close();

    emit signal_Stopped();
}

