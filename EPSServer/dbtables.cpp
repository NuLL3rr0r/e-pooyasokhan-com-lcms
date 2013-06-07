#include <MyLib/db.hpp>
#include "dbtables.hpp"
#include "rt.hpp"

using namespace std;
using namespace EPSServer;

void DBTables::InitTables()
{
    RT::Static->DB->CreateTable(RT::Static->DBTables->Table("USERS"),
                                 RT::Static->DBTables->Fields("USERS"));
}

DBTables::DBTables()
{
    InitHashes();
}

string DBTables::Table(const std::string &id)
{
    if (m_tablesHash.find(id) != m_tablesHash.end()) {
        return m_tablesHash[id];
    } else {
        return "{?}";
    }
}

string DBTables::Fields(const std::string &id)
{
    if (m_fieldsHash.find(id) != m_fieldsHash.end()) {
        return m_fieldsHash[id];
    } else {
        return "{?}";
    }
}

void DBTables::InitHashes()
{
    m_tablesHash["GROUP"] = "group";
    m_tablesHash["USERS"] = "users";

    m_fieldsHash["GROUP"] =
            " email TEXT NOT NULL, "
            " admin INTEGER NOT NULL, "
            " teacher INTEGER NOT NULL, "
            " student INTEGER NOT NULL, "
            " PRIMARY KEY ( email ASC ) ";

    m_fieldsHash["USERS"] =
            " email TEXT NOT NULL, "
            " pwd TEXT NOT NULL, "
            " first_name TEXT NOT NULL, "
            " last_name TEXT NOT NULL, "
            " vocation TEXT NOT NULL, "
            " birthday TEXT NOT NULL, "
            " educations TEXT NOT NULL, "
            " learning_experiences TEXT NOT NULL, "
            " course TEXT NOT NULL, "
            " acquaintance_method TEXT NOT NULL, "
            " province TEXT NOT NULL, "
            " phone TEXT NOT NULL, "
            " mobile TEXT NOT NULL, "
            " PRIMARY KEY ( email ASC ) ";
}

