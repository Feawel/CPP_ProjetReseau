#include "TestsFloor.h"

using namespace std;



bool TestsFloor::testFloorNumber() {
    bool result = false;
    Floor floorTest("Floor Test", 0);
    if(floorTest.getFloorNumber() == 0)
        result = true;

    return result;
}
