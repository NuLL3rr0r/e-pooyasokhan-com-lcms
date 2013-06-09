#include "audioconverter.hpp"

using namespace std;
using namespace EPSDesktop;

void AudioConverter::RawToWave(const std::string &rawFile, const std::string &waveFile,
                               unsigned int sampleRate, unsigned short channels)
{
    std::ifstream rawStream(rawFile.c_str(), std::ifstream::binary);

    rawStream.seekg(0, rawStream.end);
    size_t rawSize = rawStream.tellg();
    rawStream.seekg(0);

    unsigned char *rawBuffer = new unsigned char[rawSize];

    rawStream.read ((char *) rawBuffer, rawSize);

    rawStream.close();

    WriteWaveFromBuffer(waveFile.c_str(), rawBuffer, rawSize, sampleRate, channels);

    delete[] rawBuffer;
}

