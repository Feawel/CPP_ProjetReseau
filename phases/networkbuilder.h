#ifndef NETWORKBUILDER_H
#define NETWORKBUILDER_H

#include "model/request.h"
#include "model/location/building_building.h"

class NetworkBuilder
{
    public:
        NetworkBuilder();
        NetworkBuilder(Request* request);
        void launchP1();
        void launchP2();
        void launchP3();

    private:
        Request* request;


};

#endif // NETWORKBUILDER_H
