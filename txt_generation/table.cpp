#include "table.h"

using namespace std;

/**
 * @brief Table::getRowsSize
 * @return
 * calculate the max range of each row
 */
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

/**
 * @brief getNChar
 * @param n
 * @param str
 * @return
 * construct a string with n times the str char
 */
string getNChar(unsigned int n, char str)
{
    return string(n, str);
}

/**
 * @brief formatString
 * @param str
 * @param size
 * @return
 * format the string to center it
 */
string formatString(string str, unsigned int size)
{
    // get the blank to add and divide it by 2
    unsigned int start = (size-str.length())/2;

    // add start + 1 blank before, the string and fill the string with blank after
    return getNChar(start+1,' ')+str+getNChar(size-start-str.length()+1,' ');
}

/**
 * @brief Table::Table
 * @param rowCount : number of rows
 */
Table::Table(unsigned int rowCount):rowCount(rowCount)
{
}

/**
 * @brief Table::generateTable
 * @param file
 * generate the table from lines
 */
void Table::generateTable(ofstream& file)
{
    // get rows sizes
    vector<unsigned int> sizes = getRowsSize();

    // calculate total of each row size
    unsigned int totalSize =0;
    for(unsigned int i = 0; i< rowCount; i++)
        totalSize+=sizes[i];

    // add the first line
    // line size is total size + 2 blank by row + 1 | by row - 1 for the last row
    file << "|" + getNChar(totalSize + rowCount * 3 - 1, '-') + "|" << endl;

    for(unsigned int i = 0; i< lines.size(); i++)
    {
        vector<string> currentLine(lines[i]);
        for(unsigned int j =0; j<rowCount; j++)
        {
            // add a | at the begining of each row
            file << "|" + formatString(currentLine[j],sizes[j]);
        }
        // end of the line
        file << "|" << endl;
        // same as first line
        file << "|" + getNChar( totalSize + rowCount * 3 - 1, '-') + "|" << endl;
    }
}

/**
 * @brief Table::addLine
 * @param line
 * @return return true if success
 * add a line in lines array
 */
bool Table::addLine(std::vector<string> line)
{
    // check if line size = row number
    if(line.size()!=rowCount)
        return false;
    else
    {
        lines.push_back(line);
        return true;
    }
}
