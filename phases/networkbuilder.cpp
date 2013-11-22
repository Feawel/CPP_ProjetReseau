#include "networkbuilder.h"
#include "model/component/backbone.h"
#include "model/component/switch.h"
#include "model/component/router.h"

using namespace std;

NetworkBuilder::NetworkBuilder()
{
}


Request NetworkBuilder::getRequest() {
    return request;
}



void NetworkBuilder::launchP1(Request request) {
    Address address(10,10,0,0,16);
    Backbone backbone;

    backbone.setAddress(address);

    int i;

    buildings = request.getBuildings();

    for (i=1; i <= NB_BUILDINGS; ++i) {

        Building building;
        Address addressBuilding(10,10,i,i,NULL);


        if (building.isAdmin()) {
            Router router;
            router.setAddress(addressBuilding);
            building.addComponent(router);

        }
        else{
            Switch switchBuilding;
            switchBuilding.setAddress(addressBuilding);

            building.addComponent(switchBuilding);
        }

        buildings[i-1] = building;

    }
}

void NetworkBuilder::launchP2(Building_Building B2B) {

}

void NetworkBuilder::launchP3(Request request) {

}

void NetworkBuilder::launchP4(Request request) {

}
