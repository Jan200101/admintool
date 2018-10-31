#include "schulerparser.h"
#include <string>
#include <vector>
#include "CSVparser.h"
#include "CSVwriter.cpp"

#include <iostream>

#define DEBUG true // debug prints

// Schuler Class
void Schuler::init(int nr, std::string vorname, std::string nachname, std::string geburtsdatum, std::string username, std::string password)
{
    this->nr = nr;
    this->vorname = vorname;
    this->nachname = nachname;
    this->geburtsdatum = geburtsdatum;
    if (username.empty())
    {
        username = this->vorname + '.' + this->nachname;
    }
    this->username = username;
    if (password.empty())
    {
        password = this->geburtsdatum;
    }
    this->password = password;
}

bool Schuler::isEmpty()
{
    bool returnval = (!nr && vorname.empty() && nachname.empty() && geburtsdatum.empty());
    if (DEBUG) std::cout << "ISEMPTY " << returnval << std::endl;
    return returnval;
}

int Schuler::getNr()
{
    if (DEBUG) std::cout << "GETNR" << std::endl;
    return this->nr;
}

std::string Schuler::getVorname()
{
    if (DEBUG) std::cout << "GETVORNAME" << std::endl;
    return this->vorname;
}

std::string Schuler::getNachname()
{
    if (DEBUG) std::cout << "GETNACHNAME" << std::endl;
    return this->nachname;
}

std::string Schuler::getGeburtsdatum()
{
    if (DEBUG) std::cout << "GETGEBURTSDATUM" << std::endl;
    return this->geburtsdatum;
}

std::string Schuler::getUsername()
{
    if (DEBUG) std::cout << "GETUSERNAME" << std::endl;
    return this->username;
}

std::string Schuler::getPassword()
{
    if (DEBUG) std::cout << "GETPASSWORD" << std::endl;
    return this->password;
}

void Schuler::makeCSV(CSVWriter &csv)
{
    if (DEBUG) std::cout << "MAKECSV" << std::endl;
    csv.newRow() << this->getNr() << this->getVorname() << this->getNachname()
                 << this->getGeburtsdatum() << this->getUsername() << this->getPassword();
}

// standalone functions

// read CSV into schulerliste
void readSchuler(std::vector<Schuler> &schulerliste)
{
    short zeile = 0;
    //                                   file, delimiter, first_line_is_header?
    CsvParser *csvparser = CsvParser_new(FILENAME, ",", 0);
    CsvRow *row;

    // CsvParser_destroy_row(header); -> causes error in current version
    while ((row = CsvParser_getRow(csvparser)))
    {
        char **rowFields = CsvParser_getFields(row);

        if (DEBUG) std::cout << "READROW " << zeile << std::endl;

        schulerliste[zeile].init(atoi(rowFields[0]),
                                 std::string(rowFields[1]),
                                 std::string(rowFields[2]),
                                 std::string(rowFields[3]),
                                 std::string(rowFields[4]),
                                 std::string(rowFields[5]));
        ++zeile;

        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);
}

// write schulerliste into CSV
void writeSchuler(std::vector<Schuler> &schulerliste)
{
    CSVWriter csv(",");
    for (int i = 0; i < schulerliste.size(); ++i)
    {
        if (!schulerliste[i].isEmpty())
        {
            schulerliste[i].makeCSV(csv);
        }
        csv.writeToFile(FILENAME);
    }
}
