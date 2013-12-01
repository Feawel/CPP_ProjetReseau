#include "Tests_building_building.h"

using namespace std;

Tests_building_building::Tests_building_building()
{
}

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

    B2BTest.setVisibility(false);
    if(B2BTest.getVisibility() == false)
        testPart2 = true;

    if(testPart1 && testPart2)
        result = true;
    return result;
}

bool Tests_building_building::testExistingTechs() {
    bool result = false, testPart1 = false, testPart2 = false, testPart3 = false;
    Building* building1 = new Building("Building test 1");
    Building* building2 = new Building("Building test 2");

    Building_Building B2BTest(building1,building2,10,true);

    if(!B2BTest.existTech())
        testPart1 = true;

    B2BTest.setExistingTechnology(NTechnology::FIBER,true);
    if(B2BTest.existTech())
        testPart2 = true;
    if(B2BTest.isExistingTechs(NTechnology::FIBER))
        testPart3 = true;

    if(testPart1 && testPart2 && testPart3)
        result = true;
    return result;

}



