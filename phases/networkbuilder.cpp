/*
 *
 * networkbuilder.cpp
 *
 *  Created on: 15 nov. 2013
 *      Author: Jonathan BANON
 */


#include <sstream>
#include <typeinfo>
#include "networkbuilder.h"
#include "model/component/backbone.h"
#include "model/component/switch.h"
#include "model/component/router.h"
#include "model/request.h"
#include "model/component/firewall.h"
#include "model/constant.h"


using namespace std;

NetworkBuilder::NetworkBuilder()
{
}

NetworkBuilder::NetworkBuilder(Request* request)
{
    this->request=request;
}

int contains(vector<Building*> buildings, Building* building)
{
    for(unsigned int i = 0; i< buildings.size(); i++)
    {
        if(building == buildings[i])
            return i;
    }
    return -1;
}



/**
 * @brief NetworkBuilder::launchP1
 */
void NetworkBuilder::launchP1() {
    Address address(10,10,0,0,16);
    Backbone backbone;

    //Backbone à communiquer pour la suite !!
    backbone.setAddress(address);

    vector<Building*> buildings = request->getBuildings();

    //Définition de 2 adresses publiques (minimum pour faire un réseau)
    Address publicAddress1(190,39,43,140,31);
    Address publicAddress2(190,39,43,141,31);

    for (unsigned int i=0; i < buildings.size(); ++i) {


        Address addressBuilding(10,10,i+1,i+1,0);


        if (buildings[i]->isAdmin()) {
            /*
            On se trouve dans le batiment admin, on définit les éléments à ajouter
            soit un routeur, un firewall au niveau du batiment et un firewall
            pour l'étage admin
            */
            Router* router = new Router;
            Firewall* firewallBuilding = new Firewall;

            router->setAddress(publicAddress1);
            firewallBuilding->setAddress(addressBuilding);
            firewallBuilding->setPublicAddress(publicAddress2);

            buildings[i]->addComponent(firewallBuilding);
            buildings[i]->addComponent(router);



        }
        else{
            Switch* switchBuilding = new Switch;
            switchBuilding->setAddress(addressBuilding);

            buildings[i]->addComponent(switchBuilding);
        }
    }
}

/**
 * @brief NetworkBuilder::launchP2
 */
void NetworkBuilder::launchP2() {
    /*
     *Phase II : Technologies de liaison inter-batiments
        Définition des distances B2B
        Fibre optique (défaut)
        Paire torsadée (SI paire torsadée déjà câblée entre bâtiments)
        InfraRouge (D(B2B) < 3 && vision == true)
        Pont Wifi (D(B2B) < 0,5 && vision == true)

     */

    vector<Building_Building*> B2BFull = request->getBuilding_Buildings();
    vector<Building*> buildingsFull = request->getBuildings();

    // on créé une liste de tableaux contenant les B2B d'un bâtiment
    vector<vector<Building_Building*> > buildingB2Bs(buildingsFull.size());
    for(unsigned int i = 0; i< B2BFull.size(); i++)
    {
        Building* building1 = B2BFull[i]->getBuilding1();
        Building* building2 = B2BFull[i]->getBuilding2();
        // on récupère la position du building1 dans B2BFull et on ajoute à cette position
        // dans buildingB2BS le B2B
        buildingB2Bs[contains(buildingsFull,building1)].push_back(B2BFull[i]);
        // on récupère la position du building2 dans B2BFull et on ajoute à cette position
        // dans buildingB2BS le B2B
        buildingB2Bs[contains(buildingsFull,building2)].push_back(B2BFull[i]);
    }


    //On filtre le vector building_building afin de n'avoir que les liaisons avec technologies pré-existantes
    //auxquelles on rajoute les liaisons nécessaires pour que chaque batiment soit connecté à au moins un autre.
    vector<Building_Building*> B2BTemp(B2BFull);
    vector<Building*> listBuildingWithTech(buildingsFull.size());

    //On récupère dans un premier temps les liaisons existantes avec des techs
    // On met les abtiemtn dans listBuildingWithTech
    // On met les pointeurs des autres dans B2BTemp à 0
    for(unsigned int i=0;i<B2BTemp.size();i++){
        if(B2BTemp[i]->existTech()){
            listBuildingWithTech[contains(buildingsFull, B2BTemp[i]->getBuilding1())]=B2BTemp[i]->getBuilding1();
            listBuildingWithTech[contains(buildingsFull, B2BTemp[i]->getBuilding2())]=B2BTemp[i]->getBuilding2();
        }
        else
        {
            B2BTemp[i]=0;
        }
    }

    // si on a trouvé aucune techno on ajoute seulement le building admin dans listBuildingWithTech
    for(unsigned int  i = 0; i< buildingsFull.size(); i++)
    {
        if(buildingsFull[i]->isAdmin())
        {
            listBuildingWithTech[i]=buildingsFull[i];
            break;
        }
    }

    //On cherche ensuite les batiments connectés à aucun autre (0 dans listBuildingWithTech)
    for(unsigned int i = 0; i < listBuildingWithTech.size(); i++){
        if(listBuildingWithTech[i] == 0){
            // on récupère dans la table d'origine le bâtiment
            Building* currentBuilding = buildingsFull[i];

            // on récupère les B2B de ce bâtiment
            vector<Building_Building*> currentB2Bs = buildingB2Bs[i];

            // on parcours les liens qui arrivent à ce bâtiment
            // on sélectionne le plus court qui atteint un bâtiment de listBuildingWithTech

            double min=0;
            unsigned int minIndex =-1;
            for(unsigned int j = 0; j< currentB2Bs.size(); j++)
            {
                // on récupère l'autre batiment
                Building* otherBuilding;
                if(currentB2Bs[j]->getBuilding1()!=currentBuilding)
                    otherBuilding=currentB2Bs[j]->getBuilding1();
                else
                    otherBuilding=currentB2Bs[j]->getBuilding2();

                // si l'autre batiment est dans listBuildingWithTech on renregistre la distance
                int k = contains(listBuildingWithTech, otherBuilding);
                if(k>=0)
                {
                    double dist=currentB2Bs[k]->getDistance();
                    if(min == 0 || min > dist)
                    {
                            min = dist;
                            minIndex = j;
                    }
                }
            }

            B2BTemp.push_back(currentB2Bs[minIndex]);
            listBuildingWithTech[i]=currentBuilding;
        }
    }

    // on créé une liste de B2B en retirant tous les pointeurs à 0
    vector<Building_Building*> B2B;
    for(unsigned int i = 0; i<B2BTemp.size(); i++)
    {
        if(B2BTemp[i]!=0)
            B2B.push_back(B2BTemp[i]);
    }


    NTechnology::Technology addedTech;
    for (unsigned int i=0;i<B2B.size();i++){
        if(!B2B[i]->existTech()){

            if (B2B[i]->getDistance() < 0.5 && B2B[i]->getVisibility() == true) {
                    addedTech = NTechnology::WIFI;
                }
                else if (B2B[i]->getDistance() < 1.5 && B2B[i]->getVisibility() == true){
                    addedTech = NTechnology::INFRARED;
                }
                else {
                    addedTech = NTechnology::FIBER;
                }
        }
        else{
            vector<bool> existingTechs = B2B[i]->getExistingTechs();
            if(existingTechs[NTechnology::FIBER] == true)
            {
                addedTech = NTechnology::FIBER;
            }
            else if(existingTechs[NTechnology::TWISTEDPAIR] == true)
            {
                addedTech = NTechnology::TWISTEDPAIR;
            }
            else if(existingTechs[NTechnology::INFRARED] == true)
            {
                addedTech = NTechnology::INFRARED;
            }
            else if(existingTechs[NTechnology::WIFI] == true)
            {
                addedTech = NTechnology::WIFI;
            }

        }
    B2B[i]->setAppliedTechnology(addedTech);
    }
    request->setBuilding_Buildings(B2B);



}

/**
 * @brief NetworkBuilder::launchP3
 */
void NetworkBuilder::launchP3() {
    /*
     *Phase III : Sous réseaux intra-bâtiment
        Pour chaque étage i, bâtiment j
                Mise en place d’un L2
                Adresse du switch : 10.j.i.199
                Adresse de broadcast : 10.j.i.255
                Adresses disponibles pour DHCP : 10.j.i.200 - 10.j.i.254
                Adresse privée du réseau : 10.j.i.0/24
        Pour chaque bâtiment
                Indiquer DHCP Relay : 10.j(admin).i(admin serveurs privés).10(arbitraire)
                Indiquer Default Route : next hop : adresse privée router (coté intérieur du FW)
        Définition des règles du firewall
     */


    vector<Building*> buildings = request->getBuildings();
    for(unsigned int i=0; i < buildings.size() ;i++){


        vector<Floor*> floors = buildings[i]->getFloors();

        //Si aucun étage n'est défini, on en rajoute un correspondant à la section (ou réseau) au sein duquel évoluent les personens présentes dans ce batiment.
        if(floors.empty())
        {
            Floor* buildingFloor = new Floor("Section Builing", 0);
            buildings[i]->addSpecialSection(buildingFloor);
            floors = buildings[i]->getFloors();
        }
        for(unsigned int j=0; j < floors.size() ;j++){


            Switch* tempSwitch = new Switch;
            Address tempAddress(10,i+1,j,199,0);
            Address tempAddressBroadcast(10,i+1,j,255,0);
            Address tempAddressNetwork(10,i+1,j,0,24);
            tempSwitch->setAddress(tempAddress);


            floors[j]->addComponent(tempSwitch);
            floors[j]->setBroadcastAddress(tempAddressBroadcast);
            floors[j]->setNetworkAddress(tempAddressNetwork);

            //Vérification du nombre d'USER_SUP : pas plus de 1 pour 4 USER_DEFAULT



            /*Ajout d'étages en fonction du nombre d'utilisateurs sur chaque étage*/

            //Calcul du nombre d'utilisateurs par étage
            unsigned int NB_USER_DEFAULT = floors[j]->getUserNumber(NUserType::DEFAULT);
            unsigned int NB_USER_SUP = floors[j]->getUserNumber(NUserType::SUP);
            unsigned int NB_USER_TOT = NB_USER_DEFAULT + NB_USER_SUP;


            vector<bool> useTechs = floors[j]->getUseTechs();

            unsigned int NB_ADDED_FLOORS;
            //Nombre d'étages à ajouter dans le cas ETHERNET seul
            if(useTechs[NTechnology::ETHERNET] && !useTechs[NTechnology::WIFI])
                NB_ADDED_FLOORS = (unsigned int)(NB_USER_TOT/100);

            //Nombre d'étages à ajouter dans le cas ETHERNET + WIFI
            else if(useTechs[NTechnology::ETHERNET] && useTechs[NTechnology::WIFI])
                NB_ADDED_FLOORS = (unsigned int)(NB_USER_TOT/70);

            //Nombre d'étages à ajouter dans le cas WIFI seul
            else
                NB_ADDED_FLOORS = (unsigned int)(NB_USER_TOT/250);


            if(NB_ADDED_FLOORS > 0){
                floors[j]->setName(floors[j]->getName() + " - Section 1");
            }
            for(unsigned int k = 0; k < NB_ADDED_FLOORS; k++){
                Floor* addedFloor = buildings[i]->addFloor();
                floors.push_back(addedFloor);
                std::string stringNumFloor = Constant::numberToString(j);
                std::string stringNumSection = Constant::numberToString(k+2);
                addedFloor->setName("Floor " + stringNumFloor +" - Section " + stringNumSection);
            }




        }

        if(buildings[i]->isAdmin())
        {
            //Définition des règles des firewalls

            //Le premier a principalement une action de NAT/PAT"
            vector<Component*> components = buildings[i]->getComponents();
            Firewall* buildingFirewall(0);
            buildingFirewall=(Firewall*)components[0];
            buildingFirewall->setRules("A principalement une action de NAT/PAT. On peut également définir des règles pour bloquer l'accès internet de certains utilisateurs.' ");


            //Ajout d'un étage (cela peut correspondre à une pièce, un sous-sol etc...)
            //pour abriter les serveurs privés (destinés aux USERS_SUP)
            Firewall* privateServersFirewall = new Firewall;
            privateServersFirewall->setRules("Bloque les adresses 10.i.j.x, i et j correspondant à tous les étages et tous les batiments, et x < 200.");

            //Ajout d'un switch pour connecter cette section au réseau
            Switch* privateServersSwitch = new Switch;
            Address privateServersAddressSwitch(10,i+1,floors.size(),0,24);
            privateServersSwitch->setAddress(privateServersAddressSwitch);

            Floor* privateServersFloor= new Floor("Private Server Floor", -1);
            Address privateServersAddressBroadcast(10,i+1,floors.size(),255,0);
            Address privateServersAddressNetwork(10,i+1,floors.size(),0,24);
            privateServersFloor->setBroadcastAddress(privateServersAddressBroadcast);
            privateServersFloor->setNetworkAddress(privateServersAddressNetwork);
            privateServersFloor->addComponent(privateServersSwitch);
            privateServersFloor->addComponent(privateServersFirewall);

            buildings[i]->addSpecialSection(privateServersFloor);

            //Ajout d'un étage (cela peut correspondre à une pièce, un sous-sol, une cave etc...)
            //pour abriter la section ADMIN (destinés aux USERS_ADMIN)
            Firewall* adminFloorFirewall = new Firewall;

            // on transforme l'int du num building en string pour la concaténation
            std::string stringNumBuilding = Constant::numberToString(i+1);
            adminFloorFirewall->setRules("Bloque les adresses sources autre que 10."+stringNumBuilding+".0.x, x < 200.");

            //Ajout d'un switch pour connecter cette section au réseau
            Switch* adminSwitch = new Switch;
            Address adminAddressSwitch(10,i+1,floors.size()+1,0,24);
            adminSwitch->setAddress(adminAddressSwitch);

            Floor* adminFloor= new Floor("Admin Floor", -2);
            Address adminFloorAddressBroadcast(10,i+1,floors.size()+1,255,0);
            Address adminFloorAddressNetwork(10,i+1,floors.size()+1,0,24);
            adminFloor->setBroadcastAddress(adminFloorAddressBroadcast);
            adminFloor->setNetworkAddress(adminFloorAddressNetwork);
            adminFloor->addComponent(adminSwitch);
            adminFloor->addComponent(adminFloorFirewall);


            buildings[i]->addSpecialSection(adminFloor);



        }

    }

 }



