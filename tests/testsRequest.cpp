
#include "testsRequest.h"



bool TestsRequest::testBuilding() {
    bool result = false, testPart1 = false, testPart2 = false, testPart3 = false;

    Request request;
    if(request.getBuildings().empty())
        testPart1 = true;

    Building* newBuilding = new Building("Building test");
    request.addBuilding(newBuilding);

    if(request.getBuildings().front() == newBuilding)
        testPart2 = true;

    request.removeBuilding(0);

    if(request.getBuildings().empty())
        testPart3 = true;

    if(testPart1 && testPart2 && testPart3)
        result = true;


    return result;
}

bool TestsRequest::testB2B() {
    bool result = false, testPart1 = false, testPart2 = false, testPart3 = false;

    Request request;
    if(request.getBuilding_Buildings().empty())
        testPart1 = true;

    Building* building1 = new Building("Building test 1");
    Building* building2 = new Building("Building test 2");
    Building_Building* newB2B = new Building_Building(building1, building2);

    request.addBuilding_Building(newB2B);

    if(request.getBuilding_Buildings().front() == newB2B)
        testPart2 = true;

    request.removeBuilding_Building(0);

    if(request.getBuilding_Buildings().empty())
        testPart3 = true;

    if(testPart1 && testPart2 && testPart3)
        result = true;

    return result;
}

bool TestsRequest::testCheckData() {
    bool result = false, testPart1 = false, testPart2 = false, testPart3 = false;

    std::string atLeast2 = "You need to define at least 2 buildings";
    std::string isAdmin = "You need to define an admin building";

    Request request;
    Building* building1 = new Building("Building test 1");
    building1->setAdmin(true);
    request.addBuilding(building1);
    if(request.checkData() == atLeast2)
        testPart1 = true;

    Building* building2 = new Building("Building test 2");
    request.addBuilding(building2);
    if(request.checkData() == "")
        testPart2 = true;

    building1->setAdmin(false);
    if(request.checkData() == isAdmin)
        testPart3 = true;

    if(testPart1 && testPart2 && testPart3)
        result = true;

    return result;
}
