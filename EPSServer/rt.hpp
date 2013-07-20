#ifndef RT_HPP
#define RT_HPP


#include <memory>
#include <mutex>

namespace MyLib {
    class DB;
}

namespace EPSServer {
    class DBTables;
    class RT;
}

class EPSServer::RT
{
private:
    struct StorageStruct
    {
        std::string AppPath;
    };

    typedef std::unique_ptr<StorageStruct> Storage_ptr;
    typedef std::unique_ptr<MyLib::DB> DB_ptr;
    typedef std::unique_ptr<EPSServer::DBTables> DBTables_ptr;

private:
    static std::mutex m_storageMutex;
    static Storage_ptr m_storageInstance;

    static std::mutex m_dbMutex;
    static DB_ptr m_dbInstance;

    static std::mutex m_dbTablesMutex;
    static DBTables_ptr m_dbTablesInstance;

public:
    static StorageStruct *Storage();
    static MyLib::DB *DB();
    static EPSServer::DBTables *DBTables();
};


#endif /* RT_HPP */


