#ifndef NETWORKBUILDER_H
#define NETWORKBUILDER_H

#include "request.h"
#include "model/location/building_building.h"

class NetworkBuilder
{
    public:
        NetworkBuilder();
        NetworkBuilder(Request* request);
        Request* getRequest();
        void launchP1(Request request);
        void launchP2(std::vector<Building_Building> B2B);
        void launchP3(Request request);
        void launchP4(Request request);


    private:
        Request* request;


};

#endif // NETWORKBUILDER_H
