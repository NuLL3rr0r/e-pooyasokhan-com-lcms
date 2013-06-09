#include "audioconverter.hpp"

using namespace std;
using namespace EPSDesktop;

bool AudioConverter::RawToWave(const std::string &rawFile, const std::string &waveFile,
                               unsigned int sampleRate, unsigned short channels)
{
    std::ifstream rawStream(rawFile.c_str(), std::ifstream::binary);

    if (!rawStream.good() || !rawStream.is_open())
        return false;

    rawStream.seekg(0, rawStream.end);
    size_t rawSize = rawStream.tellg();
    rawStream.seekg(0, rawStream.beg);

    unsigned char *rawBuffer = new unsigned char[rawSize];

    rawStream.read((char *) rawBuffer, rawSize);

    rawStream.close();

    bool rc = WriteWaveFromBuffer(waveFile.c_str(), rawBuffer, rawSize, sampleRate, channels);

    delete[] rawBuffer;

    return rc;
}

