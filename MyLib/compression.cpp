#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include "compression.hpp"

using namespace boost;
using namespace MyLib;

void Compression::Compress(const CompressionBuffer_t &data, CompressionBuffer_t &out_compressed)
{
    out_compressed.clear();

    iostreams::filtering_streambuf<iostreams::output> output;
    output.push(iostreams::zlib_compressor());
    output.push(iostreams::back_inserter(out_compressed));
    iostreams::write(output, &data[0], data.size());
}

void Compression::Decompress(const CompressionBuffer_t &data, CompressionBuffer_t &out_uncompressed)
{
    out_uncompressed.clear();

    iostreams::filtering_streambuf<iostreams::output> output;
    output.push(iostreams::zlib_decompressor());
    output.push(iostreams::back_inserter(out_uncompressed));
    iostreams::write(output, &data[0], data.size());
}

