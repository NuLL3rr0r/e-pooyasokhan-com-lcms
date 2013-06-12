#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include "compression.hpp"

using namespace boost;
using namespace MyLib;

void Compression::Compress(const CompressionBuffer_t &dataBuffer,
                           CompressionBuffer_t &out_compressedBuffer)
{
    out_compressedBuffer.clear();

    iostreams::filtering_streambuf<iostreams::output> output;
    output.push(iostreams::zlib_compressor());
    output.push(iostreams::back_inserter(out_compressedBuffer));
    iostreams::write(output, &dataBuffer[0], dataBuffer.size());
}

void Compression::Decompress(const CompressionBuffer_t &dataBuffer,
                             CompressionBuffer_t &out_uncompressedBuffer)
{
    out_uncompressedBuffer.clear();

    iostreams::filtering_streambuf<iostreams::output> output;
    output.push(iostreams::zlib_decompressor());
    output.push(iostreams::back_inserter(out_uncompressedBuffer));
    iostreams::write(output, &dataBuffer[0], dataBuffer.size());
}

