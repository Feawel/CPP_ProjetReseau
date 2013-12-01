#include "TestsLocation.h"

using namespace std;

bool TestsLocation::testGetUserNumber() {
    bool result = false, testPart1 = false, testPart2 = false, testPart3 = false;
    Location location1("Location test");

    location1.setUserNumber(NUserType::DEFAULT, 300);
    unsigned int temp = location1.getUserNumber(NUserType::DEFAULT);
    if(temp == 300)
        testPart1 = true;

    location1.setUserNumber(NUserType::SUP, 30);
    temp = location1.getUserNumber(NUserType::DEFAULT);
    if(temp == 30)
        testPart2 = true;

    location1.setUserNumber(NUserType::ADMIN, 3);
    temp = location1.getUserNumber(NUserType::DEFAULT);
    if(temp == 3)
        testPart3 = true;
    if(testPart1 && testPart2 && testPart3)
        result = true;
    return result;
}

bool TestsLocation::testComponent() {
    bool result = false, testPart1 = false, testPart2 = false;
    Location location1("Location test");

    Component* component = new Component();

    if(location1.getComponents().empty())
        testPart1 = true;

    location1.addComponent(component);
    if(location1.getComponents().front() == component)
        testPart2 = true;

    if(testPart1 && testPart2)
        result = true;
    return result;
}



