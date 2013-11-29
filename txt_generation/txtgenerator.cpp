#include "txtgenerator.h"
#include "table.h"
#include "model/constant.h"
#include <iostream>
#include <fstream>

using namespace std;

TxtGenerator::TxtGenerator(Request *request, std::string folder): request(request), folder(folder)
{

}

void TxtGenerator::generateDoc()
{
    Table table(5);

    vector<string> header(5);
    header[0]="Building";
    header[1]="Floor";
    header[2]="Default Users";
    header[3]="Sup Users";
    header[4]="Admin Users";

    table.addLine(header);

    for(unsigned int i = 0; i< request->getBuildings().size(); i++)
    {
        Building* currentBuilding = request->getBuildings()[i];
        for(unsigned int j = 0; j<currentBuilding->getFloors().size(); j++ )
        {
            vector<string> line(5);
            line[0]=currentBuilding->getName();
            Floor* currentFloor = currentBuilding->getFloors()[j];
            line[1]=currentFloor->getName();
            line[2]= Constant::numberToString(currentFloor->getUserNumber(NUserType::DEFAULT));
            line[3]= Constant::numberToString(currentFloor->getUserNumber(NUserType::SUP));
            line[4]= Constant::numberToString(currentFloor->getUserNumber(NUserType::ADMIN));
            table.addLine(line);
        }
        if(currentBuilding->getFloors().empty())
        {
            vector<string> line(5);
            line[0]=currentBuilding->getName();
            line[1]="-";
            line[2]= Constant::numberToString(currentBuilding->getUserNumber(NUserType::DEFAULT));
            line[3]= Constant::numberToString(currentBuilding->getUserNumber(NUserType::SUP));
            line[4]= Constant::numberToString(currentBuilding->getUserNumber(NUserType::ADMIN));
            table.addLine(line);
        }
    }

    ofstream file((folder + "/readme.txt").c_str());
    table.generateTable(file);
}
