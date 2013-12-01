/*
 * main.cpp
 *
 *  Created on: 15 nov. 2013
 *      Author: MOULIN
 */

#include "view/requestinterface.h"
#include "graph_view/graph_generate.h"
#include <QApplication>
#include <QtGui>
#include <iostream>
#include "model/component/router.h"

#include "tests/testsBuilding.h"
#include "tests/testsComponent.h"
#include "tests/testsFirewall.h"
#include "tests/testsFloor.h"
#include "tests/testsLocation.h"
#include "tests/tests_building_building.h"
#include "tests/testsRequest.h"

using namespace std;


//mockup
#include "model/request.h"
#include <vector>
#include "model/location/building.h"
#include "model/location/building_building.h"
#include "model/constant.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Testing Classes init
    TestsBuilding testsBuilding;
    TestsComponent testsComponent;
    TestsFirewall testsFirewall;
    TestsFloor testsFloor;
    TestsLocation testsLocation;
    Tests_building_building tests_building_building;
    TestsRequest testsRequest;

    unsigned int testNumber = 14, testsPassed = 0;

    //Test of Location Class
    bool resultTestLocationComponent = testsLocation.testComponent() ;
    cout << "\nTest of Component management by a Location : " << Constant::boolToString(resultTestLocationComponent) << endl;
    bool resultTestLocationUserNumber = testsLocation.testGetUserNumber() ;
    cout << "Test of user number management in a Location : " << Constant::boolToString(resultTestLocationUserNumber) << endl;

    //Test of Building Class
    bool resultTestBuildingFloors = testsBuilding.testGetFloors();
    cout << "Test of floor(s) management by a Building : " << Constant::boolToString(resultTestBuildingFloors) << endl;
    bool resultTestBuildingAdmin = testsBuilding.testIsAdmin();
    cout << "Test of Admin\'status management by a Building : " << Constant::boolToString(resultTestBuildingAdmin) << endl;


    //Test of Floor Class
    bool resultTestFloorNumber = testsFloor.testFloorNumber();
    cout << "Test of Floor\'s number management by a Floor : " << Constant::boolToString(resultTestFloorNumber) << endl;

    //Test of Component Class
    bool resultTestComponentAddress = testsComponent.testAddress();
    cout << "Test of Address management by a Component : " << Constant::boolToString(resultTestComponentAddress) << endl;

    //Test of Firewall Class
    bool resultTestFirewallAddresses = testsFirewall.testAddresses();
    cout << "Test of multiple address management by a Firewall : " << Constant::boolToString(resultTestFirewallAddresses) << endl;
    bool resultTestFirewallRules = testsFirewall.testRules();
    cout << "Test of rules management by a Firewall : " << Constant::boolToString(resultTestFirewallRules) << endl;

    //Test of Building_building Class
    bool resultTestB2BDistance = tests_building_building.testDistance();
    cout << "Test of distance management by a Building_building : " << Constant::boolToString(resultTestB2BDistance) << endl;
    bool resultTestB2BVisibility = tests_building_building.testVisibility();
    cout << "Test of visibility management by a Building_building : " << Constant::boolToString(resultTestB2BVisibility) << endl;
    bool resultTestB2BExistingTechs = tests_building_building.testExistingTechs();
    cout << "Test of existing techs management by a Building_building : " << Constant::boolToString(resultTestB2BExistingTechs) << endl;

    //Test of Request Class
    bool resultTestRequestBuilding = testsRequest.testBuilding();
    cout << "Test of Building management by a Request : " << Constant::boolToString(resultTestRequestBuilding) << endl;
    bool resultTestRequestB2B = testsRequest.testB2B();
    cout << "Test of building_building management by a Request : " << Constant::boolToString(resultTestRequestB2B) << endl;
    bool resultTestRequestCheckData = testsRequest.testCheckData();
    cout << "Test of data checking by a Request : " << Constant::boolToString(resultTestRequestCheckData) << endl;

    //Statistics for testing
    if(resultTestB2BDistance)
        testsPassed++;
    if(resultTestB2BExistingTechs)
        testsPassed++;
    if(resultTestB2BVisibility)
        testsPassed++;
    if(resultTestBuildingAdmin)
        testsPassed++;
    if(resultTestBuildingFloors)
        testsPassed++;
    if(resultTestComponentAddress)
        testsPassed++;
    if(resultTestFirewallAddresses)
        testsPassed++;
    if(resultTestFirewallRules)
        testsPassed++;
    if(resultTestFloorNumber)
        testsPassed++;
    if(resultTestLocationComponent)
        testsPassed++;
    if(resultTestLocationUserNumber)
        testsPassed++;
    if(resultTestRequestB2B)
        testsPassed++;
    if(resultTestRequestBuilding)
        testsPassed++;
    if(resultTestRequestCheckData)
        testsPassed++;

    unsigned int testsFailed = testNumber - testsPassed;
    float statTesting  = ((float)testsPassed / (float)testNumber) * 100;
    cout << "\n Statistics : "<< testsPassed << " passed, " << testsFailed << " failed - ";
    printf("%.2f", statTesting);
    cout << "% of success" << endl;

    RequestInterface window ;
    window.show();


    return app.exec();
}
