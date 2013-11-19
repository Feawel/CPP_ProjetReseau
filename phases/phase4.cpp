//
//  phase4.cpp
//  NetworkBuilder
//
//  Created by Jonathan Banon on 19/11/2013.
//  Copyright (c) 2013 Jonathan Banon. All rights reserved.
//

#include "phase4.h"
#include "phase3.cpp"


/************************************* PHASE IV : CREATION DES SOUS-RESEAUX **************************************
 Pour chaque étage i, bâtiment j
    Mise en place d’un L2
    Adresse du switch : 10.j.i.199
    Adresse de broadcast : 10.j.i.255
    Adresses disponibles pour DHCP : 10.j.i.200 - 10.j.i.254
    Adresse privée du réseau : 10.j.i.0/24
 
 Pour chaque bâtiment
    Indiquer DHCP Relay : 10.j(admin).i(admin serveurs privés).10(arbitraire)
    Indiquer Default Route : next hop : adresse privée router (coté intérieur du FW)
 
 Global
    Creation des regles du FireWall
 */