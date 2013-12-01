#include "txtgenerator.h"
#include "model/constant.h"
#include <iostream>
#include <fstream>

using namespace std;

static const unsigned int INITIAL_BUILDING_TABLE_ROW_COUNT = 7;
static const unsigned int ADMIN_BUILDING_TABLE_ROW_COUNT = 5;
static const unsigned int DEFAULT_BUILDING_TABLE_ROW_COUNT = 4;
static const unsigned int BUILDING_BUILDING_TABLE_ROW_COUNT = 5;

TxtGenerator::TxtGenerator(std::string folder): folder(folder),
    initialTable(INITIAL_BUILDING_TABLE_ROW_COUNT)
{

}

/**
 * @brief TxtGenerator::generateInitialDataTable
 * @param request
 * generate the table with initial data
 */
void TxtGenerator::generateInitialDataTable(Request request)
{
    // create the header
    vector<string> header(INITIAL_BUILDING_TABLE_ROW_COUNT);
    header[0]="Building";
    header[1]="Floor";
    header[2]="Default Users";
    header[3]="Sup Users";
    header[4]="Admin Users";
    header[5]="Ethernet";
    header[6]="Wifi";

    // add it to the table
    initialTable.addLine(header);

    // loop on buildings
    for(unsigned int i = 0; i< request.getBuildings().size(); i++)
    {
        Building* currentBuilding = request.getBuildings()[i];
        // display each floor is ther is some
        for(unsigned int j = 0; j<currentBuilding->getFloors().size(); j++ )
        {
            vector<string> line(INITIAL_BUILDING_TABLE_ROW_COUNT);
            line[0]=currentBuilding->getName();
            Floor* currentFloor = currentBuilding->getFloors()[j];
            line[1]=currentFloor->getName();
            line[2]= Constant::numberToString(currentFloor->getUserNumber(NUserType::DEFAULT));
            line[3]= Constant::numberToString(currentFloor->getUserNumber(NUserType::SUP));
            line[4]= Constant::numberToString(currentFloor->getUserNumber(NUserType::ADMIN));

            // add techs to add in each fllor
            line[5]="Yes";
            if(!currentFloor->getUseTechs()[NTechnology::ETHERNET])
                line[5]="No";
            line[6]="Yes";
            if(!currentFloor->getUseTechs()[NTechnology::WIFI])
                line[6]="No";
            initialTable.addLine(line);
        }

        // if ther is no floors
        if(currentBuilding->getFloors().empty())
        {
            vector<string> line(INITIAL_BUILDING_TABLE_ROW_COUNT);
            line[0]=currentBuilding->getName();
            line[1]="-";
            line[2]= Constant::numberToString(currentBuilding->getUserNumber(NUserType::DEFAULT));
            line[3]= Constant::numberToString(currentBuilding->getUserNumber(NUserType::SUP));
            line[4]= Constant::numberToString(currentBuilding->getUserNumber(NUserType::ADMIN));
            line[5]="Yes";
            if(!currentBuilding->getUseTechs()[NTechnology::ETHERNET])
                line[5]="No";
            line[6]="Yes";
            if(!currentBuilding->getUseTechs()[NTechnology::WIFI])
                line[6]="No";
            initialTable.addLine(line);
        }
    }
}

/**
 * @brief TxtGenerator::publishDoc
 * @param request
 * create a doc with initail table and other data
 */
void TxtGenerator::publishDoc(Request request)
{
    // create the file
    ofstream file((folder + "/readme.txt").c_str());

    // add initial table
    file << "INITIAL DATA :" << endl;
    initialTable.generateTable(file);
    file << endl;
    file << endl;
    file << "OUTPUT DATA :" << endl;

    // create a table for each building
    vector<Building*> buildings = request.getBuildings();
    for(unsigned int i = 0; i< buildings.size(); i++)
    {
        Building* currentBuilding = buildings[i];
        if(!currentBuilding->isAdmin())
        {
            file << currentBuilding->getName() << ": backbone address " << currentBuilding->getComponents()[0]->getAddress().toString() << endl;
            file << endl;

            vector<string> header(DEFAULT_BUILDING_TABLE_ROW_COUNT);
            header[0] = "Floor";
            header[1] = "Switch";
            header[2] = "Network Address";
            header[3] = "Broadcast Address";

            Table buildingTable(DEFAULT_BUILDING_TABLE_ROW_COUNT);
            buildingTable.addLine(header);
            for(unsigned int j = 0; j< currentBuilding->getFloors().size(); j++)
            {
                vector<string> line(DEFAULT_BUILDING_TABLE_ROW_COUNT);
                line[0] = currentBuilding->getFloors()[j]->getName();
                line[1] = currentBuilding->getFloors()[j]->getComponents()[0]->getAddress().toString();
                line[2] = currentBuilding->getFloors()[j]->getNetworkAddress().toString();
                line[3] = currentBuilding->getFloors()[j]->getBroadcastAddress().toString();

                buildingTable.addLine(line);
            }
            buildingTable.generateTable(file);
            file << endl;
        }
        else
        {
            file << currentBuilding->getName() << ":" << endl;
            file << "\t- Public Address Router: " << currentBuilding->getComponents()[1]->getAddress() << endl;
            file << "\t- Public Address Firewall: " << ((Firewall*)currentBuilding->getComponents()[0])->getPublicAddress() << endl;
            file << "\t- Backbone Address: " << currentBuilding->getComponents()[0]->getAddress() << endl;
            file << "\t- Firewall Rule: " << ((Firewall*)currentBuilding->getComponents()[0])->getRules() << endl;
            file << endl;

            vector<string> header(ADMIN_BUILDING_TABLE_ROW_COUNT);
            header[0] = "Floor";
            header[1] = "Switch";
            header[2] = "Firewall";
            header[3] = "Network Address";
            header[4] = "Broadcast Address";

            Table buildingTable(ADMIN_BUILDING_TABLE_ROW_COUNT);
            buildingTable.addLine(header);
            for(unsigned int j = 0; j< currentBuilding->getFloors().size(); j++)
            {
                vector<string> line(ADMIN_BUILDING_TABLE_ROW_COUNT);
                line[0] = currentBuilding->getFloors()[j]->getName();
                line[1] = currentBuilding->getFloors()[j]->getComponents()[0]->getAddress().toString();
                line[2] = "No";
                if(currentBuilding->getFloors()[j]->getComponents().size()>1)
                    line[2] = ((Firewall*)currentBuilding->getFloors()[j]->getComponents()[1])->getRules();
                line[3] = currentBuilding->getFloors()[j]->getNetworkAddress().toString();
                line[4] = currentBuilding->getFloors()[j]->getBroadcastAddress().toString();

                buildingTable.addLine(line);
            }
            buildingTable.generateTable(file);
            file << endl;
        }
    }

    file << "Links :" << endl;
    file << endl;

    Table b2bTable(BUILDING_BUILDING_TABLE_ROW_COUNT);
    vector<string> header(BUILDING_BUILDING_TABLE_ROW_COUNT);
    header[0] = "Building";
    header[1] = "Building";
    header[2] = "Connection Technology";
    header[3] = "Distance";
    header[4] = "Visibility";

    vector<Building_Building*> b2bs = request.getBuilding_Buildings();
    for(unsigned int i = 0; i< b2bs.size(); i++)
    {
        Building_Building* currentB2B = b2bs[i];
        vector<string> line(BUILDING_BUILDING_TABLE_ROW_COUNT);
        line[0] = currentB2B->getBuilding1()->getName();
        line[1] = currentB2B->getBuilding2()->getName();
        NTechnology::Technology tech = currentB2B->getAppliedTechnology();
        switch (tech) {
        case NTechnology::FIBER:
            line[2] = "Fiber";
            break;

        case NTechnology::TWISTEDPAIR:
            line[2] = "Twisted Pair";
            break;

        case NTechnology::WIFI:
            line[2] = "WiFi";
            break;

        case NTechnology::INFRARED:
            line[2] = "Infra-Red";
            break;
        }
        line[3] = Constant::numberToString(currentB2B->getDistance());
        bool visibility = currentB2B->getVisibility();
        if(visibility)
            line[4] = "Yes";
        else
            line[4] = "No";

        b2bTable.addLine(line);
    }
    b2bTable.generateTable(file);
}
