#ifndef TXTGENERATOR_H
#define TXTGENERATOR_H

#include "model/request.h"
#include "table.h"

class TxtGenerator
{
public:
    TxtGenerator(std::string folder);
    void generateInitialDataTable(Request request);
    void publishDoc(Request request);
private:
    std::string folder;
    Table initialTable;
};

#endif // TXTGENERATOR_H
