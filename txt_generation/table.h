#ifndef TABLE_H
#define TABLE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Table
{
public:
    Table(unsigned int rowCount);
    void generateTable(std::ofstream& file);
    bool addLine(std::vector<std::string> line);
private:
    unsigned int rowCount;
    std::vector<std::vector<std::string> > lines;
    std::vector<unsigned int> getRowsSize() const;
};

#endif // TABLE_H
