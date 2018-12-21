#include "userparser.hpp"
#include <iostream>
#include "CSVParser.hpp"
#include "CSVWriter.hpp"

std::vector<User> readUser(std::string filename)
{
    std::vector<User> userliste;
    CSVParser csv(filename);
    std::vector<std::string> row;

    for (unsigned short entry = 0; !csv.eof(); ++entry)
    {
        row = csv.getrow();
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
    writeUser(userliste, filename);
    return userliste;
}

void writeUser(std::vector<User>& userliste, std::string filename)
{
    CSVWriter csv;

    for (User& entry : userliste)
    {
        csv.newRow() << entry.getVorname() << entry.getNachname() << entry.getUsername();
    }

    csv.writeToFile(filename);
}