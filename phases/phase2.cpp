//
//  phase2.cpp
//  NetworkBuilder
//
//  Created by Jonathan Banon on 19/11/2013.
//  Copyright (c) 2013 Jonathan Banon. All rights reserved.
//

#include "phase2.h"
#include "phase1.cpp"
#include "link.h"
#include "building_building.h"



/************************************* PHASE II : TECHNOLOGIES DE LIAISON INTER-BATIMENTS **************************************
 Définition des distances B2B
    Fibre optique (défaut)
    Paire torsadée (SI paire torsadée déjà câblée entre bâtiments)
    InfraRouge (D(B2B) < 3 && vision == true)
    Pont Wifi (D(B2B) < 0,5 && vision == true)
 
 
 */



    Building_Building B2B(buildings[i], buildings[j],tabDistanceB2B[i][j] , tabVisibilityB2B2[i][j]);
    
    
    if (B2B.getDistance() < 0.5 && B2B.getVisibility() == true) {
        B2B.addExistingTechnology(WIFI);
        
    }
    else if (B2B.getDistance() < 3 && B2B.getVisibility() == true){
        B2B.addExistingTechnology(INFRARED);
    }
    else (B2B.getDistance()){
        B2B.addExistingTechnology(FIBER);
    }
