#ifndef TXTGENERATOR_H
#define TXTGENERATOR_H

#include "phases/Request.h"

class TxtGenerator
{
public:
    TxtGenerator(Request *request, std::string folder);
    void generateDoc();
private:
    Request *request;
    std::string folder;
};

#endif // TXTGENERATOR_H
