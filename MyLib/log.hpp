#ifndef LOG_HPP
#define LOG_HPP


#include <fstream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>

namespace MyLib {
    class Log;
}

class MyLib::Log
{
public:
    enum class EType : unsigned char {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    struct ETypeHasher
    {
        std::size_t operator()(const EType &t) const
        {
            return std::hash<unsigned char>()(static_cast<unsigned char>(t));
        }
    };

private:
    struct StorageStruct
    {
        bool MultiStream;
        bool Initialized;

        std::unordered_map<Log::EType, std::string, ETypeHasher> LogTypeHash;

        std::ostream *LogOutputStream;

        std::ofstream LogOutputFileStream;
        std::string LogOutputDirectoryPath;
        std::string LogOutputFilePrefix;
        std::string LogOutputFilePath;        
    };

    typedef std::unique_ptr<StorageStruct> Storage_ptr;

private:
    static std::mutex m_storageMutex;
    static Storage_ptr m_storageInstance;

    static std::mutex m_logMutex;

private:
    std::ostringstream m_buffer;
    bool m_hasEntries;

public:
    static void Initialize(std::ostream &out_outputStream);
    static void Initialize(const std::string &outputDirectoryPath,
                           const std::string &outputFilePrefix);
    static void Initialize(std::ostream &out_outputStream,
                           const std::string &outputDirectoryPath,
                           const std::string &outputFilePrefix);

private:
    static StorageStruct *Storage();

public:
    Log(EType type, const std::string &file, const std::string &func, int line, ...);
    ~Log();

    template<typename T>
    Log &operator,(const T &arg)
    {
        if (m_hasEntries)
            m_buffer << "\n";
        m_buffer << "  - " << arg;
        m_hasEntries = true;
        return *this;
    }
};


#define LOG_TRACE(...)  \
    (MyLib::Log(MyLib::Log::EType::Trace, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define LOG_DEBUG(...)  \
    (MyLib::Log(MyLib::Log::EType::Debug, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define LOG_INFO(...)  \
    (MyLib::Log(MyLib::Log::EType::Info, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define LOG_WARNING(...)  \
    (MyLib::Log(MyLib::Log::EType::Warning, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define LOG_ERROR(...)  \
    (MyLib::Log(MyLib::Log::EType::Error, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;

#define LOG_FATAL(...)  \
    (MyLib::Log(MyLib::Log::EType::Fatal, __FILE__, __FUNCTION__, __LINE__)), __VA_ARGS__;


#endif /* LOG_HPP */

