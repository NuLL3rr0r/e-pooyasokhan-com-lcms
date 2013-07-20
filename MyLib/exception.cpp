#include "exception.hpp"

using namespace std;
using namespace MyLib;

Exception::Exception(const string &message)
    : runtime_error(message)
{
}


