#include <cstdarg>
#include <sqlite3.h>
#include <cppdb/backend.h>
#include <cppdb/driver_manager.h>
#include "db.hpp"

using namespace std;
using namespace cppdb;
using namespace MyLib;

#if defined ( MYLIB_STATIC )
bool DB::m_isSQLite3DriverLoaded = false;
#endif  // defined ( MYLIB_STATIC )

#ifdef MYLIB_STATIC
extern "C" {
    cppdb::backend::connection *cppdb_sqlite3_get_connection(cppdb::connection_info const &);
}
#endif  // defined ( MYLIB_STATIC )

#ifdef MYLIB_STATIC
void DB::LoadSQLite3Driver()
{
    if (!m_isSQLite3DriverLoaded) {
        m_isSQLite3DriverLoaded = true;
        cppdb::driver_manager::instance()
                .install_driver("sqlite3",
                                new cppdb::backend::static_driver(cppdb_sqlite3_get_connection));
    }
}
#endif  // defined ( MYLIB_STATIC )

bool DB::Vacuum(const std::string &dbFile)
{
    sqlite3 *db;

    int rc = sqlite3_open(dbFile.c_str(), &db);
    if (!rc) {
        sqlite3_exec(db, "VACUUM;", 0, 0, 0);
        return true;
    }

    return false;
}

DB::DB(const string &dbFile)
{
    m_sql.open("sqlite3:db=" + dbFile);
}

DB::~DB()
{
    m_sql.close();
}

cppdb::session &DB::Sql()
{
    return m_sql;
}

void DB::CreateTable(const std::string &table, const std::string &fields)
{
    m_sql << "CREATE TABLE IF NOT EXISTS [" + table + "] ("
             + fields
             + ");"
          << exec;
}

void DB::DropTable(const std::string &table)
{
    m_sql << "DROP TABLE IF EXISTS [" + table + "];"
          << exec;
}

void DB::Insert(const std::string &table, const std::string &fields, const int count, ...)
{
    va_list args;
    va_start(args, count);

    string ph;
    for (int i = 0; i < count; ++i) {
        if (i != 0)
            ph += ", ";
        ph += "?";
    }

    statement stat = m_sql << "INSERT OR IGNORE INTO [" + table + "] "
                              "(" + fields + ") "
                              "VALUES (" + ph + ");";

    for(int i = 0; i < count; ++i) {
         stat.bind(va_arg(args, char*));
    }

    va_end(args);

    stat.exec();
}

void DB::Update(const std::string &table, const std::string &where, const std::string &value,
                const std::string &set, const int count, ...)
{
    va_list args;
    va_start(args, count);

    statement stat = m_sql << "UPDATE [" + table + "] "
                              "SET " + set + " "
                              "WHERE " + where + "=?;";

    for(int i = 0; i < count; ++i) {
         stat.bind(va_arg(args, char*));
    }

    va_end(args);

    stat.bind(value);

    stat.exec();
}

void DB::Delete(const std::string &table, const std::string &where, const std::string &value)
{
    m_sql << "DELETE FROM [" + table + "] "
             "WHERE " + where + "=?;"
          << value
          << exec;
}

