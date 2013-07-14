#include <cassert>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/format.hpp>
#include "make_unique.hpp"
#include "log.hpp"

using namespace MyLib;

std::mutex Log::m_storageMutex;
Log::Storage_ptr Log::m_storageInstance;

std::mutex Log::m_logMutex;

void Log::Initialize(std::ostream &out_outputStream)
{
    if (Storage()->Initialized)
        return;

    Storage()->LogOutputStream = &out_outputStream;

    if (!Storage()->MultiStream)
        Storage()->Initialized = true;
}

void Log::Initialize(const std::string &outputDirectoryPath,
                     const std::string &outputFilePrefix)
{
    if (Storage()->Initialized)
        return;

    Storage()->LogOutputDirectoryPath = outputDirectoryPath;
    Storage()->LogOutputFilePrefix = outputFilePrefix;

    if (boost::filesystem::exists(Storage()->LogOutputDirectoryPath)) {
        if (!boost::filesystem::is_directory(Storage()->LogOutputDirectoryPath)) {
            boost::filesystem::remove(Storage()->LogOutputDirectoryPath);
        }
    }

    if (!boost::filesystem::exists(Storage()->LogOutputDirectoryPath)) {
        boost::filesystem::create_directories(Storage()->LogOutputDirectoryPath);
    }

    Storage()->LogOutputFilePath =
            (boost::filesystem::path(Storage()->LogOutputDirectoryPath)
             / boost::filesystem::path((boost::format("%1%_%2%.txt")
                                        % Storage()->LogOutputFilePrefix
                                        % boost::algorithm::replace_all_copy(
                                            boost::algorithm::replace_all_copy(
                                                boost::posix_time::to_simple_string(
                                                    boost::posix_time::second_clock::local_time()),
                                                ":", "-"),
                                            " ", "_")).str())).string();

    if (!Storage()->MultiStream)
        Storage()->Initialized = true;
}

void Log::Initialize(std::ostream &out_outputStream,
                     const std::string &outputDirectoryPath,
                     const std::string &outputFilePrefix)
{
    if (Storage()->Initialized)
        return;

    Storage()->MultiStream = true;

    Initialize(out_outputStream);
    Initialize(outputDirectoryPath, outputFilePrefix);

    Storage()->Initialized = true;
}

Log::StorageStruct *Log::Storage()
{
    std::lock_guard<std::mutex> lock(m_storageMutex);
    (void)lock;

    if (m_storageInstance == nullptr) {
        m_storageInstance = std::make_unique<StorageStruct>();

        m_storageInstance->MultiStream = false;
        m_storageInstance->Initialized = false;

        m_storageInstance->LogTypeHash.clear();
        m_storageInstance->LogTypeHash[Log::EType::Trace] = "Trace";
        m_storageInstance->LogTypeHash[Log::EType::Debug] = "Debug";
        m_storageInstance->LogTypeHash[Log::EType::Info] = "Info";
        m_storageInstance->LogTypeHash[Log::EType::Warning] = "Warning";
        m_storageInstance->LogTypeHash[Log::EType::Error] = "Error";
        m_storageInstance->LogTypeHash[Log::EType::Fatal] = "Fatal";

        m_storageInstance->LogOutputStream = NULL;

        if (m_storageInstance->LogOutputFileStream.is_open())
            m_storageInstance->LogOutputFileStream.close();

        m_storageInstance->LogOutputDirectoryPath.clear();;
        m_storageInstance->LogOutputFilePrefix.clear();;
        m_storageInstance->LogOutputFilePath.clear();;
    }

    return m_storageInstance.get();
}

Log::Log(EType type, const std::string &file, const std::string &func, int line, ...)
    : m_hasEntries(false)
{
    assert(Storage()->Initialized);

    m_buffer << "[ " << boost::posix_time::second_clock::local_time()
             << " " << Storage()->LogTypeHash[type]
                << " " << line << " " << func << " " << file << " ]"
                << "\n";
}

Log::~Log()
{
    m_buffer << "\n\n";
    m_buffer.flush();

    std::lock_guard<std::mutex> lock(m_logMutex);
    (void)lock;

    if (Storage()->LogOutputStream) {
        (*Storage()->LogOutputStream) << m_buffer.str();
        Storage()->LogOutputStream->flush();
    }

    if (Storage()->LogOutputFilePath != "") {
        if(!Storage()->LogOutputFileStream.is_open()) {
            Storage()->LogOutputFileStream.open(
                        Storage()->LogOutputFilePath,
                        std::ios_base::out | std::ios_base::app);
            Storage()->LogOutputFileStream.imbue(
                        std::locale(
                            Storage()->LogOutputFileStream.getloc(),
                            new boost::posix_time::time_facet()));
        }

        Storage()->LogOutputFileStream << m_buffer.str();
        Storage()->LogOutputFileStream.flush();
        Storage()->LogOutputFileStream.close();
    }
}

