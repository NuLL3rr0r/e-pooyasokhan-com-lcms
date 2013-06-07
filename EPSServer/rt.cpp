#include <MyLib/db.hpp>
#include <MyLib/make_unique.hpp>
#include "rt.hpp"
#include "dbtables.hpp"

using namespace std;
using namespace EPSServer;

const std::string RT::StaticStuff::DB_FILE_NAME = "eps.db";

RT::StaticStuff_ptr RT::Static(std::make_unique<RT::StaticStuff>());

RT::StaticStuff::StaticStuff()
    : DB(std::make_unique<MyLib::DB>(AppPath + RT::StaticStuff::DB_FILE_NAME)),
      DBTables(std::make_unique<EPSServer::DBTables>())
{
}

RT::StaticStuff::~StaticStuff()
{
    DB.reset();
    DBTables.reset();
}

