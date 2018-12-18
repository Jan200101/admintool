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
    std::string s;
    std::vector<std::string> list;

    if (!std::getline(this->filestream, s))
    {
        return list;
    }

    size_t pos = 0;

    while ((pos = s.find(this->seperator)) != std::string::npos)
    {
        list.resize(list.size() + 1);
        list[list.size() - 1] = s.substr(0, pos);
        s.erase(0, pos + this->seperator.length());
    }
    list.resize(list.size() + 1);
    list[list.size() - 1] = s;
    return list;
}