/*
 *
 * networkbuilder.cpp
 *
 *  Created on: 15 nov. 2013
 *      Author: Jonathan BANON
 */


#include <sstream>
#include "networkbuilder.h"
#include "model/component/backbone.h"
#include "model/component/switch.h"
#include "model/component/router.h"
#include "phases/request.h"
#include "model/component/firewall.h"
#include "model/link.h"


using namespace std;

NetworkBuilder::NetworkBuilder()
{
}

NetworkBuilder::NetworkBuilder(Request* request)
{
    this->request=request;
}


Request* NetworkBuilder::getRequest() {
    return request;
}



void NetworkBuilder::launchP1() {
    Address address(10,10,0,0,16);
    Backbone backbone;

    backbone.setAddress(address);

    int i;

    vector<Building*> buildings = request->getBuildings();

    //Définition de 2 adresses publiques (minimum pour faire un réseau)
    Address publicAddress1(190,39,43,140,31);
    Address publicAddress2(190,39,43,141,31);

    for (i=0; i < buildings.size(); ++i) {


        Address addressBuilding(10,10,i+1,i+1,0);


        if (buildings[i]->isAdmin()) {
            /*
            On se trouve dans le batiment admin, on définit les éléments à ajouter
            soit un routeur, un firewall au niveau du batiment et un firewall
            pour l'étage admin
            */
            Router router;
            Firewall firewallBuilding;
            Firewall firewallFloor;

            router.setAddress(publicAddress1);
            firewallBuilding.setAddress(addressBuilding);
            firewallBuilding.setPublicAddress(publicAddress2);

            buildings[i]->addComponent(router);
            buildings[i]->addComponent(firewallBuilding);



        }
        else{
            Switch switchBuilding;
            switchBuilding.setAddress(addressBuilding);

            buildings[i]->addComponent(switchBuilding);
        }


    }
}

void NetworkBuilder::launchP2() {
    /*
     *Phase II : Technologies de liaison inter-batiments
        Définition des distances B2B
        Fibre optique (défaut)
        Paire torsadée (SI paire torsadée déjà câblée entre bâtiments)
        InfraRouge (D(B2B) < 3 && vision == true)
        Pont Wifi (D(B2B) < 0,5 && vision == true)

     */

    vector<Building_Building*> B2B = request->getBuilding_Buildings();

    int i;

    //Tableau de Link qui contiendra les liens entre les batiments et les technologies associées
    vector<Link> linksBetweenBuildings;

    for (i=0;i<B2B.size();i++){

        vector<NTechnology::Technology> existingTechs = B2B[i]->getExistingTechs();

        if(existingTechs.empty()){
            if (B2B[i]->getDistance() < 0.5 && B2B[i]->getVisibility() == true) {
                    B2B[i]->addExistingTechnology(NTechnology::WIFI);

                }
                else if (B2B[i]->getDistance() < 3 && B2B[i]->getVisibility() == true){
                    B2B[i]->addExistingTechnology(NTechnology::INFRARED);
                }
                else {
                    B2B[i]->addExistingTechnology(NTechnology::FIBER);
                }
            NTechnology::Technology addedTech = B2B[i]->getExistingTechs().front();
            Link newLink(&B2B[i]->getBuilding1()->getComponents().front(), &B2B[i]->getBuilding2()->getComponents().front(), addedTech);
            linksBetweenBuildings[i] = newLink;
        }
        else{
            Link newLink(&B2B[i]->getBuilding1()->getComponents().front(), &B2B[i]->getBuilding2()->getComponents().front(), existingTechs.front());
            linksBetweenBuildings[i] = newLink;
        }


    }



}

void NetworkBuilder::launchP3() {
    /*
     *Phase III : Liaisons intra-batiment
        Différents récepteurs possibles
                Routeur FAI (bat admin)
                Switch L2/3 (autres batiments)
                Récepteur toit (IR ou Pont Wifi)
                Récepteur sous sol (fibre ou cable)
        Création d’un Local Technique pour chaque étage
                Entre chaque local fibre optique multimode
                2,5 prises ethernet/personne pour chaque étage
     */





}

void NetworkBuilder::launchP4() {
    /*
     *Phase IV : Sous réseaux intra-bâtiment
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

    int i,j;


    vector<Building*> buildings = request->getBuildings();
    for(i=0; i < buildings.size() ;i++){


        vector<Floor*> floors = buildings[i]->getFloors();

        for(j=0; j < floors.size() ;j++){


            Switch tempSwitch;
            Address tempAddress(10,j+1,i+1,199,0);
            Address tempAddressBroadcast(10,j+1,i+1,255,0);
            Address tempAddressNetwork(10,j+1,i+1,0,24);
            tempSwitch.setAddress(tempAddress);


            floors[j]->addComponent(tempSwitch);


            floors[j]->addComponent(tempSwitch);
            floors[j]->setBroadcastAddress(tempAddressBroadcast);
            floors[j]->setNetworkAddress(tempAddressNetwork);

            if(buildings[i]->isAdmin())
            {
                //Définition des règles des firewalls
                //Le premier bloque l'accès aux serveurs privés
                //pour les "default user"

                vector<Component> components = buildings[i]->getComponents();
                Firewall* buildingFirewall = buildings[i]->getFirewall(components);
                buildingFirewall->setRules("A principalement une action de NAT/PAT. On peut également définir des règles pour bloquer l'accès internet de certains utilisateurs.' ");


                //Ajout d'un étage (cela peut correspondre à une pièce, un sous-sol etc...)
                //pour abriter les serveurs privés (destinés aux USERS_SUP)
                Firewall privateServersFirewall;
                privateServersFirewall.setRules("Bloque les adresses 10.i.j.x, i et j correspondant à tous les étages et tous les batiments, et x < 200.");
                Floor privateServersFloor("Private Server Floor", -1);
                privateServersFloor.addComponent(privateServersFirewall);
                buildings[i]->addSpecialSection(&privateServersFloor);

                //Ajout d'un étage (cela peut correspondre à une pièce, un sous-sol, une cave etc...)
                //pour abriter la section ADMIN (destinés aux USERS_ADMIN)
                Firewall adminFloorFirewall;

                // créer un flux de sortie
                std::ostringstream oss;
                // écrire un nombre dans le flux
                oss << i+1;
                // récupérer une chaîne de caractères
                std::string stringNumBuilding = oss.str();

                adminFloorFirewall.setRules("Bloque les adresses sources autre que 10."+stringNumBuilding+".0.x, x < 200.");
                Floor adminFloor("Admin Floor", -2);
                adminFloor.addComponent(adminFloorFirewall);
                buildings[i]->addSpecialSection(&adminFloor);



            }


        }

    }
 }


