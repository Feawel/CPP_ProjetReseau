//
//  Request.h
//  NetworkBuilder
//
//  Created by Jonathan Banon on 21/11/2013.
//  Copyright (c) 2013 Jonathan Banon. All rights reserved.
//

#ifndef __NetworkBuilder__Request__
#define __NetworkBuilder__Request__

#include <iostream>
#include "../model/location/building.h"

class Request{

public:
    Request();
    std::vector<Building> getBuildings();
    void addBuilding(Building newBuilding);
    void removeBuilding(int id);


private:
    std::vector<Building> buildings;
};



#endif /* defined(__NetworkBuilder__Request__) */
