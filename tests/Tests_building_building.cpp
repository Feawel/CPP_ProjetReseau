#include "Tests_building_building.h"

using namespace std;

bool Tests_building_building::testDistance() {
    bool result = false;
    Building* building1 = new Building("Building test 1");
    Building* building2 = new Building("Building test 2");

    Building_Building B2BTest(building1,building2,10,true);

    if(B2BTest.getDistance() == 10)
        result = true;
    return result;
}

bool Tests_building_building::testVisibility() {
    bool result = false, testPart1 = false, testPart2 = false;
    Building* building1 = new Building("Building test 1");
    Building* building2 = new Building("Building test 2");

    Building_Building B2BTest(building1,building2,10,true);

    if(B2BTest.getVisibility() == true)
        testPart1 = true;


    return result;
}

bool Tests_building_building::testExistingTechs() {

}



