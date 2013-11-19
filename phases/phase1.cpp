//
//  phase1.cpp
//  NetworkBuilder
//
//  Created by Jonathan Banon on 19/11/2013.
//  Copyright (c) 2013 Jonathan Banon. All rights reserved.
//

#include "phase0.cpp"
#include "phase1.h"

#include "component.h"
#include "address.h"
#include "backbone.h"
#include "switch.h"
#include "router.h"
#include "building.h"

#include <iostream>

/************************************* PHASE I : CREATION DU BACKBONE **************************************
 
    Adresse du backbone : 10.10.0.0/16
    Un switch L2/3 par bâtiment
    Une adresse par bâtiment : pour chaque bâtiment i
        10.10.i.i
    Un bâtiment désigné comme « Bat Admin » (Bat admin à TRUE ?)

*/
using namespace std;

int main() {
    Address address(10,10,0,0,16);
    Backbone backbone;
    
    
    
    backbone.setAddress(address);
    
    int i;
    
    
    Building buildings[NB_BUILDINGS];
    
    for (i=1; i <= NB_BUILDINGS; ++i) {
        
        //Classe Building à créer
        Building building;
        Address addressBuilding(10,10,i,i,NULL);

        
        if (building.isAdmin()) {
            Router router;
            router.setAddress(addressBuilding);
            building.addComponent(router);
            
            Address addressBuilding(10,10,i,i,NULL);
        }
        else{
            Switch switchBuilding;
            switchBuilding.setAddress(addressBuilding);
            
            building.addComponent(switchBuilding);
        }
        
        buildings[i-1] = building;
        
    }
    
}

    
    
    

