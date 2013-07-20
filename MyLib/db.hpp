#ifndef DB_HPP
#define DB_HPP


#include <string>
#include <cppdb/frontend.h>

namespace MyLib {
    class DB;
}

class MyLib::DB
{
private:
#ifdef MYLIB_STATIC
    static bool m_isSQLite3DriverLoaded;
#endif  // MYLIB_STATIC

private:
    cppdb::session m_sql;

public:
#ifdef MYLIB_STATIC
    static void LoadSQLite3Driver();
#endif  // MYLIB_STATIC

    static bool Vacuum(const std::string &dbFile);

public:
    DB(const std::string &dbFile);
    ~DB();

    cppdb::session &SQL();

    void CreateTable(const std::string &table, const std::string &fields);
    void DropTable(const std::string &table);

    void Insert(const std::string &table, const std::string &fields, const int count, ...);
    void Update(const std::string &table, const std::string &where, const std::string &value,
                const std::string &set, const int count, ...);
    void Delete(const std::string &table, const std::string &where, const std::string &value);
};


#endif /* DB_HPP */


