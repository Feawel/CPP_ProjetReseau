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
