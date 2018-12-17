#include "userparser.hpp"
#include "CSVParser.hpp"
#include "CSVWriter.hpp"

void readUser(std::vector<User>& userliste)
{
    unsigned short entry = 0;
    CSVParser csv(FILENAME);
    std::vector<std::string> row;

    for (; ((row = csv.getrow()).size() != 0); ++entry)
    {
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
}

void writeUser(std::vector<User>& userliste)
{
    CSVWriter csv;

    for (User& entry : userliste)
    {
        csv.newRow() << entry.getVorname() << entry.getNachname() << entry.getUsername();
    }

    csv.writeToFile(FILENAME);
}