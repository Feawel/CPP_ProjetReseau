#include "testsComponent.h"



bool TestsComponent::testAddress() {
    bool result = false;
    Component componentTest;

    Address addressTest(10,8,6,4,2);

    componentTest.setAddress(addressTest);

    Address addressTest2 = componentTest.getAddress();

    std::string addressTestString = addressTest.toString();
    std::string addressTest2String = addressTest2.toString();

    if(addressTestString == addressTest2String)
        result = true;
    return result;
}
