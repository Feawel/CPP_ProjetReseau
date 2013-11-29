#ifndef TXTGENERATOR_H
#define TXTGENERATOR_H

#include "phases/Request.h"
#include "table.h"

class TxtGenerator
{
public:
    TxtGenerator(std::string folder);
    void generateInitialDataTable(Request request);
    void publishDoc();
private:
    std::string folder;
    Table initialTable;
};

#endif // TXTGENERATOR_H
