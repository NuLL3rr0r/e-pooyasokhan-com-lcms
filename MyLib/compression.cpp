#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include "compression.hpp"
#include "log.hpp"

#define     COMP_ERROR          "Unknow compression error!";
#define     DECOMP_ERROR        "Unknow decompression error!";

using namespace boost;
using namespace MyLib;

void Compression::Compress(const char *data, size_t size,
                           CompressionBuffer_t &out_compressedBuffer)
{
    const Compression::CompressionBuffer_t buffer(data, data + size);
    Compress(buffer, out_compressedBuffer);
}

void Compression::Compress(const std::string &dataString,
                           CompressionBuffer_t &out_compressedBuffer)
{
    const CompressionBuffer_t buffer(dataString.begin(), dataString.end());
    Compress(buffer, out_compressedBuffer);
}

void Compression::Compress(const CompressionBuffer_t &dataBuffer,
                           CompressionBuffer_t &out_compressedBuffer)
{
    try {
        out_compressedBuffer.clear();

        iostreams::filtering_streambuf<iostreams::output> output;
        output.push(iostreams::zlib_compressor());
        output.push(iostreams::back_inserter(out_compressedBuffer));
        iostreams::write(output, &dataBuffer[0], dataBuffer.size());
    } catch(...) {
        LOG_ERROR(COMP_ERROR)
    }
}

void Compression::Decompress(const CompressionBuffer_t &dataBuffer,
                             std::string &out_uncompressedString)
{
    CompressionBuffer_t buffer;
    Decompress(dataBuffer, buffer);
    out_uncompressedString = std::string(buffer.begin(), buffer.end());
}

void Compression::Decompress(const CompressionBuffer_t &dataBuffer,
                             CompressionBuffer_t &out_uncompressedBuffer)
{
    try {
        out_uncompressedBuffer.clear();

        iostreams::filtering_streambuf<iostreams::output> output;
        output.push(iostreams::zlib_decompressor());
        output.push(iostreams::back_inserter(out_uncompressedBuffer));
        iostreams::write(output, &dataBuffer[0], dataBuffer.size());
    } catch(...) {
        LOG_ERROR(DECOMP_ERROR)
    }
}

