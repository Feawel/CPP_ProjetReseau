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

using namespace std;


//mockup
#include "model/request.h"
#include <vector>
#include "model/location/building.h"
#include "model/location/building_building.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TestsBuilding testsBuilding;
    TestsComponent testsComponent;
    TestsFirewall testsFirewall;
    TestsFloor testsFloor;
    TestsLocation testsLocation;
    Tests_building_building tests_building_building;

    RequestInterface window ;
    window.show();


    return app.exec();
}
