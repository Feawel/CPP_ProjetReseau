#include "txtgenerator.h"
#include "model/constant.h"
#include <iostream>
#include <fstream>

using namespace std;

static const unsigned int BUILDING_TABLE_ROW_COUNT = 7;

TxtGenerator::TxtGenerator(std::string folder): folder(folder),
    initialTable(BUILDING_TABLE_ROW_COUNT)
{

}

void TxtGenerator::generateInitialDataTable(Request request)
{
    vector<string> header(BUILDING_TABLE_ROW_COUNT);
    header[0]="Building";
    header[1]="Floor";
    header[2]="Default Users";
    header[3]="Sup Users";
    header[4]="Admin Users";
    header[5]="Ethernet";
    header[6]="Wifi";

    initialTable.addLine(header);

    for(unsigned int i = 0; i< request.getBuildings().size(); i++)
    {
        Building* currentBuilding = request.getBuildings()[i];
        for(unsigned int j = 0; j<currentBuilding->getFloors().size(); j++ )
        {
            vector<string> line(BUILDING_TABLE_ROW_COUNT);
            line[0]=currentBuilding->getName();
            Floor* currentFloor = currentBuilding->getFloors()[j];
            line[1]=currentFloor->getName();
            line[2]= Constant::numberToString(currentFloor->getUserNumber(NUserType::DEFAULT));
            line[3]= Constant::numberToString(currentFloor->getUserNumber(NUserType::SUP));
            line[4]= Constant::numberToString(currentFloor->getUserNumber(NUserType::ADMIN));
            line[5]="Yes";
            if(!currentFloor->getUseTechs()[NTechnology::ETHERNET])
                line[5]="No";
            line[6]="Yes";
            if(!currentFloor->getUseTechs()[NTechnology::WIFI])
                line[6]="No";
            initialTable.addLine(line);
        }
        if(currentBuilding->getFloors().empty())
        {
            vector<string> line(BUILDING_TABLE_ROW_COUNT);
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

void TxtGenerator::publishDoc()
{
    ofstream file((folder + "/readme.txt").c_str());
    initialTable.generateTable(file);
}
