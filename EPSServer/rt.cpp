#include <MyLib/db.hpp>
#include "rt.hpp"
#include "dbtables.hpp"

using namespace std;
using namespace EPSServer;

const std::string RT::DB_FILE_NAME = "eps.db";

RT::StaticStuff::StaticStuff()
    : DBTables_(new DBTables())
{
}

RT::StaticStuff::~StaticStuff()
{
    DB_.reset();
    DBTables_.reset();
}

void RT::StaticStuff::Initialize()
{
    DB_ = DB_ptr(new MyLib::DB(AppPath + RT::DB_FILE_NAME));
}

RT::StaticStuff_ptr RT::Static(new RT::StaticStuff());

