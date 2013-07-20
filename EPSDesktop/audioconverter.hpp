#ifndef AUDIOCONVERTER_HPP
#define AUDIOCONVERTER_HPP


#include <fstream>
#include <string>

namespace EPSDesktop {
    class AudioConverter;
}

class EPSDesktop::AudioConverter
{
public:
    static bool RawToWave(const std::string &rawFile, const std::string &waveFile,
                          unsigned int sampleRate, unsigned short channels);

private:
    template <typename T>
    static void WriteToStream(std::ofstream& stream, const T &t) {
        stream.write((const char *)&t, sizeof(T));
    }

    template <typename SampleType>
    static bool WriteWaveFromBuffer(const char *outFile, SampleType *buffer, size_t bufferSize,
                                    unsigned int sampleRate, unsigned short channels)
    {
        std::ofstream stream(outFile, std::ios::binary);

        if (!stream.is_open())
            return false;

        stream.write("RIFF", 4);
        WriteToStream<int>(stream, 36 + bufferSize);
        stream.write("WAVE", 4);
        stream.write("fmt ", 4);
        WriteToStream<int>(stream, 16);
        WriteToStream<short>(stream, 1);                                        // Format (1 = PCM)
        WriteToStream<short>(stream, channels);                                 // Channels
        WriteToStream<int>(stream, sampleRate);                                 // Sample Rate
        WriteToStream<int>(stream, sampleRate * channels * sizeof(SampleType)); // Byterate
        WriteToStream<short>(stream, channels * sizeof(SampleType));            // Frame size
        WriteToStream<short>(stream, 8 * sizeof(SampleType));                   // Bits per sample
        stream.write("data", 4);
        stream.write((const char *)&bufferSize, 4);
        stream.write((const char *)buffer, bufferSize);

        return true;
    }
};


#endif /* AUDIOCONVERTER_HPP */


