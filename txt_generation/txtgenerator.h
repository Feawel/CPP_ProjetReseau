#ifndef TXTGENERATOR_H
#define TXTGENERATOR_H

#include "phases/Request.h"

class TxtGenerator
{
public:
    TxtGenerator(Request *request);
    void generateDoc();
private:
    Request *request;
};

#endif // TXTGENERATOR_H
