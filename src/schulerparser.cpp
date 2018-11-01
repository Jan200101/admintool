#include "schulerparser.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "CSVparser.h"
#include "CSVwriter.cpp"

#define DEBUG 1   // debug prints
#define NOWRITE 1 // stop writing DEBUG

// Schuler Class
void Schuler::init(int nr, std::string vorname, std::string nachname,
                   short geburtsjahr, short geburtsmonat, short geburtstag,
                   std::string username, std::string password)
{
    this->enabled = true;

    this->nr = nr;

    this->vorname = vorname;
    this->nachname = nachname;

    this->geburtsdatum[0] = geburtsjahr;
    this->geburtsdatum[1] = geburtsmonat;
    this->geburtsdatum[2] = geburtstag;

    if (username.empty())
    {
        username = this->vorname + '.' + this->nachname;
    }
    this->username = username;
    if (password.empty())
    {
        password = std::to_string(geburtstag) + "." + std::to_string(geburtsmonat) + "." + std::to_string(geburtsjahr);
    }
    this->password = password;
}

void Schuler::init(int nr, std::string vorname, std::string nachname,
                   short geburtsjahr, short geburtsmonat, short geburtstag)
{
    this->init(nr, vorname, nachname, geburtsjahr, geburtsmonat, geburtstag, "", "");
}

int Schuler::getNr()
{
    if (DEBUG) std::cout << "[DEBUG]GETNR" << std::endl;
    return this->nr;
}

std::string Schuler::getVorname()
{
    if (DEBUG) std::cout << "[DEBUG]GETVORNAME" << std::endl;
    return this->vorname;
}

std::string Schuler::getNachname()
{
    if (DEBUG) std::cout << "[DEBUG]GETNACHNAME" << std::endl;
    return this->nachname;
}

short *Schuler::getGeburtsdatum()
{
    if (DEBUG) std::cout << "[DEBUG]GETGEBURTSDATUM" << std::endl;

    short *buffer = (short *)malloc(3);
    if (buffer == NULL) exit(1);

    *buffer = *this->geburtsdatum;

    return buffer;
}

std::string Schuler::getUsername()
{
    if (DEBUG) std::cout << "[DEBUG]GETUSERNAME" << std::endl;
    return this->username;
}

std::string Schuler::getPassword()
{
    if (DEBUG) std::cout << "[DEBUG]GETPASSWORD" << std::endl;
    return this->password;
}

void Schuler::makeCSV(CSVWriter &csv)
{
    if (DEBUG) std::cout << "[DEBUG]MAKECSV" << std::endl;
    csv.newRow() << this->nr << this->vorname << this->nachname
                 << this->geburtsdatum[0] << this->geburtsdatum[1]
                 << this->geburtsdatum[2] << this->username << this->password;
}

// standalone functions

// read CSV into schulerliste
void readSchuler(std::vector<Schuler> &schulerliste)
{
    short entry = 0;
    //                                   file, delimiter, first_line_is_header?
    CsvParser *csvparser = CsvParser_new(FILENAME, ",", 0);
    CsvRow *row;

    // CsvParser_destroy_row(header) ; -> causes error in current version
    while ((row = CsvParser_getRow(csvparser)))
    {
        if (DEBUG) std::cout << "[DEBUG]READROW " << entry << std::endl;

        char **rowFields = CsvParser_getFields(row);

        schulerliste[entry].init(atoi(rowFields[0]),
                                 std::string(rowFields[1]),
                                 std::string(rowFields[2]),
                                 atoi(rowFields[3]),
                                 atoi(rowFields[4]),
                                 atoi(rowFields[5]),
                                 std::string(rowFields[6]),
                                 std::string(rowFields[7]));
        ++entry;

        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);
}

// write schulerliste into CSV
void writeSchuler(std::vector<Schuler> &schulerliste)
{
    CSVWriter csv(",");

    for (long unsigned int i = 0; i < schulerliste.size(); ++i)
    {
        if (DEBUG && !NOWRITE) std::cout << "[DEBUG]WRITEROW " << i << std::endl;

        if (schulerliste[i].enabled)
        {
            schulerliste[i].makeCSV(csv);
        }
        csv.writeToFile(FILENAME);
    }
}

// append to schulerliste
void appendSchuler(std::vector<Schuler> &schulerliste,
                   std::string vorname, std::string nachname,
                   short geburtsjahr, short geburtsmonat, short geburtstag)
{
    short entry = 0;
    while (schulerliste[entry].enabled) ++entry;

    if (DEBUG) std::cout << "[DEBUG]APPENDROW " << entry << std::endl;

    schulerliste[entry].init(schulerliste[entry - 1].getNr() + 1,
                             vorname, nachname,
                             geburtsjahr, geburtsmonat, geburtstag);
}