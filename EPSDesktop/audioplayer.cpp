#include <QDebug>
#include <MyLib/make_unique.hpp>
#include "audioplayer.hpp"

using namespace std;
using namespace EPSDesktop;

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent)
{
    Initialize();
}

AudioPlayer::AudioPlayer(const QString &filePath, QObject *parent)
    : QObject(parent)
{
    m_file = make_unique<QFile>(filePath);

    Initialize();
}


AudioPlayer::~AudioPlayer()
{
    if (m_isFileOpen || m_isPlaying)
        Stop();
}

void AudioPlayer::OnStateChanged(QAudio::State newState)
{
    switch (newState) {
    case QAudio::IdleState:
        // Finished playing (no more data)
        Stop();
        break;

    case QAudio::StoppedState:
        // Stopped for other reasons
        if (m_audioOutput->error() != QAudio::NoError) {
            // Error handling
        }
        break;

    default:
        // ... other cases as appropriate
        break;
    }

    emit signal_StateChanged(newState);
}

QString AudioPlayer::GetFilePath() const
{
    return m_file->fileName();
}

void AudioPlayer::SetFilePath(const QString &filePath)
{
    if (m_isPlaying)
        return;

    m_file->setFileName(filePath);
}

QList<QAudioDeviceInfo> AudioPlayer::GetDevicesList() const
{
    return QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
}

qreal AudioPlayer::GetVolume() const
{
    return m_audioOutput->volume();
}

void AudioPlayer::SetVolume(qreal vol)
{
    m_audioOutput->setVolume(vol);
}

void AudioPlayer::Start()
{
    if (m_isPlaying)
        return;

    m_isPlaying = true;

    m_audioOutput->reset();
    m_file->open(QIODevice::ReadOnly);
    m_audioOutput->start(m_file.get());

    m_isFileOpen = true;
}

void AudioPlayer::Stop()
{
    if (!m_isPlaying)
        return;

    m_audioOutput->stop();
    m_file->close();
    m_audioOutput->reset();

    m_isFileOpen = false;
    m_isPlaying = false;
}

void AudioPlayer::Resume()
{
    if (!m_isFileOpen)
        return;

    if (m_isPlaying)
        return;

    m_isPlaying = true;

    m_audioOutput->resume();
}

void AudioPlayer::Pause()
{
    if (!m_isFileOpen)
        return;

    if (!m_isPlaying)
        return;

    m_audioOutput->suspend();

    m_isPlaying = false;
}

void AudioPlayer::Initialize()
{
    m_isFileOpen = false;
    m_isPlaying = false;

    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    m_audioOutput = make_unique<QAudioOutput>(format, this);
    connect(m_audioOutput.get(), SIGNAL(stateChanged(QAudio::State)),
            this, SLOT(OnStateChanged(QAudio::State)));
}

