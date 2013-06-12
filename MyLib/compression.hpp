#ifndef COMPRESSION_HPP
#define COMPRESSION_HPP


namespace MyLib {
    class Compression;
}

class MyLib::Compression
{
public:
    typedef std::vector<char> CompressionBuffer_t;

public:
    static void Compress(const CompressionBuffer_t &data, CompressionBuffer_t &out_compressed);
    static void Decompress(const CompressionBuffer_t &data, CompressionBuffer_t &out_uncompressed);
};


#endif /* COMPRESSION_HPP */


