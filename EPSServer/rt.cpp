#include <MyLib/db.hpp>
#include <MyLib/make_unique.hpp>
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
    DB_ = std::make_unique<MyLib::DB>(AppPath + RT::DB_FILE_NAME);
}

RT::StaticStuff_ptr RT::Static(std::make_unique<RT::StaticStuff>());

