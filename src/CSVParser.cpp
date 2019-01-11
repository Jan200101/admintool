#include "CSVParser.hpp"
#include <iostream>

/**
 * @file CSVParser.cpp
 * @brief Source file for CSVParser
 *
 * Contains definitions for the CSVParser class
 */

CSVParser::~CSVParser()
{
    this->filestream.close();
}

/**
 * @param filename set what file to use
 * @param separator set what separator to use.
 * Default seperator ";" is defined in defines.h
 */
CSVParser::CSVParser(std::string filename, std::string separator)
{
    this->filestream.open(filename);
    this->separator = separator;
}

/**
 * @brief returns EOF status
 * @return bool
 * @retval 1 if EOF is reached otherwise 0
 */
bool CSVParser::eof()
{
    return this->filestream.eof();
}

/**
 * @return string vector
 */
std::vector<std::string> CSVParser::getRow()
{
    std::vector<std::string> values;

    if (this->eof())
    {
        return values;
    }

    std::string row;
    std::getline(this->filestream, row);

    size_t pos = 0;

    while ((pos = row.find(this->separator)) != std::string::npos)
    {
        values.push_back(row.substr(0, pos));
        row.erase(0, pos + this->separator.length());
    }
    values.push_back(row);
    return values;
}