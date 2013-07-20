#ifndef COMPRESSION_HPP
#define COMPRESSION_HPP


#include <string>
#include <vector>

namespace MyLib {
    class Compression;
}

class MyLib::Compression
{
public:
    typedef std::vector<char> CompressionBuffer_t;

public:
    static void Compress(const char *data, size_t size,
                         CompressionBuffer_t &out_compressedBuffer);
    static void Compress(const std::string &dataString,
                         CompressionBuffer_t &out_compressedBuffer);
    static void Compress(const CompressionBuffer_t &dataBuffer,
                         CompressionBuffer_t &out_compressedBuffer);
    static void Decompress(const CompressionBuffer_t &dataBuffer,
                           std::string &out_uncompressedString);
    static void Decompress(const CompressionBuffer_t &dataBuffer,
                           CompressionBuffer_t &out_uncompressedBuffer);
};


#endif /* COMPRESSION_HPP */


