#include "table.h"

using namespace std;

vector<unsigned int> Table::getRowsSize() const
{
    vector<unsigned int> sizes(rowCount,0);
    for(unsigned int i = 0 ; i< lines.size(); i++)
    {
        for(unsigned int j = 0; j< rowCount; j++)
        {
            unsigned int currentSize = lines[i][j].size();
            if(sizes[j] < currentSize)
                sizes[j]=currentSize;
        }
    }
    return sizes;
}

string getNChar(unsigned int n, char str)
{
    return string(n, str);
}

string formatString(string str, unsigned int size)
{
    unsigned int start = (size-str.length())/2;
    return getNChar(start+1,' ')+str+getNChar(size-start-str.length()+1,' ');
}

Table::Table(unsigned int rowCount):rowCount(rowCount)
{
}

void Table::generateTable(ofstream& file)
{

    vector<unsigned int> sizes = getRowsSize();
    unsigned int totalSize =0;
    for(unsigned int i = 0; i< rowCount; i++)
        totalSize+=sizes[i];

    file<<"|"+getNChar(totalSize+rowCount*3-1,'-')+"|"<<endl;

    for(unsigned int i = 0; i< lines.size(); i++)
    {
        vector<string> currentLine(lines[i]);
        for(unsigned int j =0; j<rowCount; j++)
        {
            file<<"|" + formatString(currentLine[j],sizes[j]);
        }
        file << "|" << endl;
        file << "|"+getNChar(totalSize+rowCount*3-1,'-')+"|" << endl;
    }
}

bool Table::addLine(std::vector<string> line)
{
    if(line.size()!=rowCount)
        return false;
    else
    {
        lines.push_back(line);
        return true;
    }
}
