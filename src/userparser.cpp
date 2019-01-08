#include "userparser.hpp"
#include "CSVParser.hpp"
#include "CSVWriter.hpp"

/**
 * @file userparser.cpp
 * @brief Source file for user parsing functions
 *
 * Contains definitions for user parsing functions
 */

/**
 * @return vector of the User class
 *
 * Returns a vector containing the User class initialized via the contents of a CSV read by CSVParser
 */
std::vector<User> readUser()
{
    std::vector<User> userliste;
    CSVParser csv(FILENAME);
    std::vector<std::string> row;

    for (unsigned short entry = 0; !csv.eof(); ++entry)
    {
        row = csv.getRow();
        userliste.resize(entry + 1);

        if (row.size() == 3)
        {
            userliste[entry].init(row[0], row[1], row[2]);
        }
        else
        {
            userliste[entry].init(row[0], row[1], "");
        }
    }
    writeUser(userliste);
    return userliste;
}

/**
 * @param userliste vector pointer containing the User class
 *
 * writes the contents contents of userliste to a CSV file. The default path "res/schuler.csv" is defined in defines.h
 */
void writeUser(std::vector<User>& userliste)
{
    writeUser(userliste, FILENAME);
}

/**
 * @param userliste vector pointer containing the User class
 * @param filename string
 *
 * writes the contents contents of userliste to a CSV file.
 */
void writeUser(std::vector<User>& userliste, std::string filename)
{
    CSVWriter csv;

    for (User& entry : userliste)
    {
        csv.newRow() << entry.getVorname() << entry.getNachname() << entry.getUsername();
    }

    csv.writeToFile(filename);
}