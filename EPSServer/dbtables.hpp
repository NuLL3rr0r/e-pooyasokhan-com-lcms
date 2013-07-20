#ifndef DBTABLES_HPP
#define DBTABLES_HPP


#include <string>
#include <unordered_map>

namespace EPSServer {
    class DBTables;
}

class EPSServer::DBTables
{
private:
    std::unordered_map<std::string, std::string> m_tablesHash;
    std::unordered_map<std::string, std::string> m_fieldsHash;

public:
    static void InitTables();

public:
    DBTables();

    std::string Table(const std::string &id);
    std::string Fields(const std::string &id);

private:
    void InitHashes();
};


#endif /* DBTABLES_HPP */


