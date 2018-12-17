#ifndef CSVWRITER_H // include guard
#define CSVWRITER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "defines.h"

class CSVWriter
{
   protected:
    bool firstRow;
    std::string seperator;
    int amount; // number of columns
    std::stringstream stream;

   public:
    CSVWriter();
    CSVWriter(std::string seperator);

    CSVWriter& add(char* str);
    CSVWriter& add(const char* str);
    CSVWriter& add(std::string str);

    template <typename T>
    CSVWriter& add(T str)
    {
        if (this->amount > 0) this->stream << this->seperator;
        this->stream << str;
        this->amount++;
        return *this;
    }

    template <typename T>
    CSVWriter& operator<<(const T& t)
    {
        return this->add(t);
    }

    std::string toString();

    CSVWriter& newRow();

    bool writeToFile(std::string filename);
};

#endif