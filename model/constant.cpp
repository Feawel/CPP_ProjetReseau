#include "constant.h"
#include <sstream>
#include <string>

using namespace std;

string Constant::numberToString(int number)
{
    ostringstream ss;
    ss << number;
    return ss.str();
}

string Constant::boolToString(bool booleen)
{
    if (booleen)
        return "OK !";
    else
        return "Failed...";
}
