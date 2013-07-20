#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP


#include <memory>
#include <QFile>
#include <QObject>
#include <QString>
#include <QtMultimedia/QAudioOutput>

namespace EPSDesktop {
    class AudioPlayer;
}

class EPSDesktop::AudioPlayer : public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<QFile> m_file;
    std::unique_ptr<QAudioOutput> m_audioOutput;

    bool m_isFileOpen;
    bool m_isPlaying;

public:
    explicit AudioPlayer(QObject *parent = 0);
    explicit AudioPlayer(const QString &filePath, QObject *parent = 0);
    ~AudioPlayer();

signals:
    void signal_StateChanged(QAudio::State newState);

private slots:
    void OnStateChanged(QAudio::State newState);

public:
    QString GetFilePath() const;
    void SetFilePath(const QString &filePath);

    qreal GetVolume() const;
    void SetVolume(qreal vol);

    QList<QAudioDeviceInfo> GetDevicesList() const;

    void Start();
    void Stop();
    void Resume();
    void Pause();

private:
    void Initialize();
};


#endif /* AUDIOPLAYER_HPP */


