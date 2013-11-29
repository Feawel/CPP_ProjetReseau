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
#include "../model/location/building_building.h"
#include "model/link.h"

class Request{

public:
    Request();
    Request(std::vector<Building*> b,std::vector<Building_Building*> b2b);
    std::vector<Building*> getBuildings();
    void addBuilding(Building* newBuilding);
    void removeBuilding(int id);
    std::vector<Building_Building*> getBuilding_Buildings();
    void addBuilding_Building(Building_Building* newBuilding_Buildings);
    void removeBuilding_Building(int id);
    void generateGraphText();
    void setLinks(std::vector<Link*> newLinks);
    std::vector<Link*> getLinks() const;

private:
    std::vector<Building*> buildings;
    std::vector<Building_Building*> building_buildings;
    std::vector<Link*> links;
};

#endif /* defined(__NetworkBuilder__Request__) */
