#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <fstream>
#include <string>
#include <vector>
#include "defines.h"

class CSVParser
{
   private:
    std::ifstream filestream;
    std::string seperator;

   public:
    CSVParser();
    ~CSVParser();
    CSVParser(std::string filename);
    CSVParser(std::string filename, std::string seperator);

    bool eof();

    std::vector<std::string> getrow();
};

#endif