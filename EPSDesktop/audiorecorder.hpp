#ifndef AUDIORECORDER_HPP
#define AUDIORECORDER_HPP


#include <memory>
#include <QFile>
#include <QObject>
#include <QString>
#include <QtMultimedia/QAudioInput>

namespace EPSDesktop {
    class AudioRecorder;
}

class EPSDesktop::AudioRecorder : public QObject
{
    Q_OBJECT

private:
    std::unique_ptr<QFile> m_file;
    std::unique_ptr<QAudioInput> m_audioInput;

    bool m_isFileOpen;
    bool m_isRecording;

public:
    explicit AudioRecorder(QObject *parent = 0);
    explicit AudioRecorder(const QString &filePath, QObject *parent = 0);
    ~AudioRecorder();

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


#endif /* AUDIORECORDER_HPP */


