#include "CSVWriter.hpp"

CSVWriter::CSVWriter()
{
    this->firstRow = true;
    this->seperator = DEFAULTSEPERATOR; // standart seperator
    this->amount = 0;
}

CSVWriter::CSVWriter(std::string seperator)
{
    this->firstRow = true;
    this->seperator = seperator; // standart seperator
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

std::string CSVWriter::toString()
{
    return this->stream.str();
}

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

bool CSVWriter::writeToFile(std::string filename)
{
    std::ofstream filestream;
    filestream.open(filename.c_str(), std::ios::out | std::ios::trunc);
    if (!filestream.is_open()) return false;

    filestream << this->toString();
    filestream.close();
    return filestream.good();
}