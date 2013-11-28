/*
 * constant.h
 *
 *  Created on: 17 nov. 2013
 *      Author: MOULIN
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <string>

class Constant
{
public:
    static std::string numberToString(int number);
};

namespace NTechnology {

typedef enum {
    WIFI, ETHERNET, FIBER, INFRARED, TWISTEDPAIR
} Technology;
}

namespace NUserType
{
typedef enum {
    DEFAULT = 0, SUP = 1, ADMIN = 2
} UserType;
}
#endif /* CONSTANT_H_ */
