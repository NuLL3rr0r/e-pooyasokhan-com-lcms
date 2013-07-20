#include <boost/format.hpp>
#include <QDebug>
#include <MyLib/exception.hpp>
#include <MyLib/make_unique.hpp>
#include "audiorecorder.hpp"

using namespace std;
using namespace boost;
using namespace MyLib;
using namespace EPSDesktop;

AudioRecorder::AudioRecorder(QObject *parent)
    : QObject(parent)
{
    Initialize();
}

AudioRecorder::AudioRecorder(const QString &filePath, QObject *parent)
    : QObject(parent)
{
    m_file = make_unique<QFile>(filePath);

    Initialize();
}

AudioRecorder::~AudioRecorder()
{
    if (m_isFileOpen || m_isRecording)
        Stop();
}

void AudioRecorder::OnStateChanged(QAudio::State newState)
{
    switch (newState) {
    case QAudio::StoppedState:
        if (m_audioInput->error() != QAudio::NoError) {
            // Error handling
        } else {
            // Finished recording
        }
        break;

    case QAudio::ActiveState:
        // Started recording - read from IO device
        break;

    default:
        // ... other cases as appropriate
        break;
    }

    emit signal_StateChanged(newState);
}

QString AudioRecorder::GetFilePath() const
{
    return m_file->fileName();
}

void AudioRecorder::SetFilePath(const QString &filePath)
{
    if (m_isRecording)
        return;

    m_file->setFileName(filePath);
}

qreal AudioRecorder::GetVolume() const
{
    return m_audioInput->volume();
}

void AudioRecorder::SetVolume(qreal vol)
{
    m_audioInput->setVolume(vol);
}

QList<QAudioDeviceInfo> AudioRecorder::GetDevicesList() const
{
    return QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
}

void AudioRecorder::Start()
{
    if (m_isRecording)
        return;

    m_isRecording = true;

    m_audioInput->reset();

    if (!m_file->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        throw MyLib::Exception((boost::format("Could not open file %1% for recording.")
                                % GetFilePath().toStdString()).str());
    }

    m_audioInput->start(m_file.get());

    m_isFileOpen = true;
}

void AudioRecorder::Stop()
{
    if (!m_isRecording)
        return;

    m_audioInput->stop();
    m_file->close();
    m_audioInput->reset();

    m_isFileOpen = false;
    m_isRecording = false;
}

void AudioRecorder::Resume()
{
    if (!m_isFileOpen)
        return;

    if (m_isRecording)
        return;

    m_isRecording = true;

    m_audioInput->resume();
}

void AudioRecorder::Pause()
{
    if (!m_isFileOpen)
        return;

    if (!m_isRecording)
        return;

    m_audioInput->suspend();

    m_isRecording = false;
}

void AudioRecorder::Initialize()
{
    m_isFileOpen = false;
    m_isRecording = false;

    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported by backend, "
                      "trying to use the nearest.";
        format = info.nearestFormat(format);
    }

    m_audioInput = make_unique<QAudioInput>(format, this);
    connect(m_audioInput.get(), SIGNAL(stateChanged(QAudio::State)),
            this, SLOT(OnStateChanged(QAudio::State)));
}

