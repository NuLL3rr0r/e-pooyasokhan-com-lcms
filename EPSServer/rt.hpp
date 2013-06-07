#ifndef RT_HPP
#define RT_HPP


#include <memory>
#include <string>

namespace MyLib {
    class DB;
}

namespace EPSServer {
    class DBTables;
    class RT;
}

class EPSServer::RT
{
    friend class StaticStuff;

public:
    class StaticStuff {
    private:
        static const std::string DB_FILE_NAME;

    public:
        typedef std::unique_ptr<MyLib::DB> DB_ptr;
        typedef std::unique_ptr<EPSServer::DBTables> DBTables_ptr;

    public:
        std::string AppPath;
        DB_ptr DB;
        DBTables_ptr DBTables;

    public:
        StaticStuff();
        ~StaticStuff();
    };

public:
    typedef std::unique_ptr<StaticStuff> StaticStuff_ptr;

public:
    static StaticStuff_ptr Static;
};


#endif /* RT_HPP */


