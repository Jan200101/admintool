#include "CSVWriter.hpp"

/**
 * @file CSVWriter.cpp
 * @brief Source file for CSVWriter
 *
 * Contains definitions for the CSVWriter class
 */

/** 
 * Default Constructor
 *
 * Separator defaults to ";" defined in defines.h
 */
CSVWriter::CSVWriter()
{
    this->firstRow = true;
    this->separator = DEFAULTSEPARATOR;
    this->amount = 0;
}

/**
 * @param separator set what separator to use.
 */
CSVWriter::CSVWriter(std::string separator)
{
    this->firstRow = true;
    this->separator = separator;
    this->amount = 0;
}

CSVWriter& CSVWriter::add(char* str)
{
    return this->add(std::string(str));
}

CSVWriter& CSVWriter::add(const char* str)
{
    return this->add(std::string(str));
}

CSVWriter& CSVWriter::add(std::string str)
{
    return this->add<std::string>(str);
}

/**
 * @brief returns the stringstreams content added via the << operator
 * @return string
 * @retval stringstream content
 */
std::string CSVWriter::toString()
{
    return this->stream.str();
}

/**
 * @return CSVWriter
 * @retval return class of method
 */
CSVWriter& CSVWriter::newRow()
{
    if (!this->firstRow)
    {
        stream << std::endl;
    }
    else
    {
        this->firstRow = false;
    }
    amount = 0;
    return *this;
}

/**
 * @brief returns EOF status
 * @param filename path to output file
 * @return bool
 * @retval 1 if no errors occured otherwise 0
 */
bool CSVWriter::writeToFile(std::string filename)
{
    std::ofstream filestream;
    filestream.open(filename.c_str(), std::ios::out | std::ios::trunc);
    if (!filestream.is_open()) return false;

    filestream << this->toString();
    filestream.close();
    return filestream.good();
}