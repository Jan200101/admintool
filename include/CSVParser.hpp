#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <fstream>
#include <string>
#include <vector>
#include "defines.h"

/**
 * @file CSVParser.hpp
 * @brief Header for CSVParser
 *
 * Contains declarations for the CSVParser class
 */

/**
 * @brief Simple CSV file parsing class
 *
 * a simple class designed to parse CSV files
 * does not support special behavior like quotes
 */
class CSVParser
{
   private:
    std::ifstream filestream;
    std::string separator;

   public:
    CSVParser();
    ~CSVParser();
    CSVParser(std::string filename, std::string seperator = DEFAULTSEPARATOR);

    bool eof();

    std::vector<std::string> getRow();
};

#endif