#include "CSVParser.hpp"
#include <iostream>

CSVParser::~CSVParser()
{
    this->filestream.close();
}

CSVParser::CSVParser(std::string filename)
{
    this->filestream.open(filename);
    this->seperator = DEFAULTSEPERATOR;
}

CSVParser::CSVParser(std::string filename, std::string seperator)
{
    this->filestream.open(filename);
    this->seperator = seperator;
}

bool CSVParser::eof()
{
    return this->filestream.eof();
}

std::vector<std::string> CSVParser::getrow()
{
    std::vector<std::string> values;

    if (this->eof())
    {
        return values;
    }

    std::string row;
    std::getline(this->filestream, row);

    size_t pos = 0;

    while ((pos = row.find(this->seperator)) != std::string::npos)
    {
        values.push_back(row.substr(0, pos));
        row.erase(0, pos + this->seperator.length());
    }
    values.push_back(row);
    values.shrink_to_fit();
    return values;
}