#ifndef CSVWRITER_H // include guard
#define CSVWRITER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "defines.h"

/**
 * @file CSVWriter.hpp
 * @brief Header for CSVWriter
 *
 * Contains declarations for the CSVHeader class
 */

/**
 * @brief Simple CSV writing class
 *
 * a simple class designed to make files
 * does not support special behavior like quotes
 */
class CSVWriter
{
   protected:
    bool firstRow;
    std::string separator;
    int amount; // number of columns
    std::stringstream stream;

   public:
    CSVWriter();
    CSVWriter(std::string separator);

    CSVWriter& add(char* str);
    CSVWriter& add(const char* str);
    CSVWriter& add(std::string str);

    template <typename T>
    CSVWriter& add(T str)
    {
        if (this->amount > 0) this->stream << this->separator;
        this->stream << str;
        this->amount++;
        return *this;
    }

    template <typename T>
    /**
     * @brief adds a string or C string to the active stringstream
     * @return CSVWriter
     * @retval return class of method
     */
    CSVWriter& operator<<(const T& t)
    {
        return this->add(t);
    }

    std::string toString();

    CSVWriter& newRow();

    bool writeToFile(std::string filename);
};

#endif