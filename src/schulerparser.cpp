#include "schulerparser.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "CSVparser.h"
#include "CSVwriter.cpp"

#define DEBUG 0
#define NOMAKECSV 0 // stop makeCSV DEBUG, useful tesing anything
#define NOGETNR 0   // stop getNr DEBUG, useful when appening a lot

// Schuler Class
void Schuler::init(unsigned short nr, unsigned short permissionlevel,
                   std::string vorname, std::string nachname,
                   unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
                   std::string username, std::string password)
{
    this->enabled = true;

    this->nr = nr;

    this->permissionlevel = permissionlevel;

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

void Schuler::init(unsigned short nr, unsigned short permissionlevel,
                   std::string vorname, std::string nachname,
                   unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag)
{
    this->init(nr, permissionlevel,
               vorname, nachname,
               geburtsjahr, geburtsmonat, geburtstag,
               "", "");
}

unsigned short Schuler::getNr()
{
    if (DEBUG && !NOGETNR) std::cout << "[DEBUG] GETNR" << std::endl;
    return this->nr;
}

unsigned short Schuler::getPermission()
{
    if (DEBUG) std::cout << "[DEBUG] GETPERMISSION" << std::endl;
    return this->permissionlevel;
}

std::string Schuler::getVorname()
{
    if (DEBUG) std::cout << "[DEBUG] GETVORNAME" << std::endl;
    return this->vorname;
}

std::string Schuler::getNachname()
{
    if (DEBUG) std::cout << "[DEBUG] GETNACHNAME" << std::endl;
    return this->nachname;
}

unsigned short* Schuler::getGeburtsdatum()
{
    unsigned short* datum = (unsigned short*)std::malloc(3);

    datum = this->geburtsdatum;

    return datum;
}

unsigned short Schuler::getGeburtsjahr()
{
    if (DEBUG) std::cout << "[DEBUG] GETGEBURTSJAHR" << std::endl;
    return this->geburtsdatum[0];
}

unsigned short Schuler::getGeburtsmonat()
{
    if (DEBUG) std::cout << "[DEBUG] GETGEBURTSMONAT" << std::endl;
    return this->geburtsdatum[1];
}

unsigned short Schuler::getGeburtstag()
{
    if (DEBUG) std::cout << "[DEBUG] GETGEBURTSTAG" << std::endl;
    return this->geburtsdatum[2];
}

std::string Schuler::getUsername()
{
    if (DEBUG) std::cout << "[DEBUG] GETUSERNAME" << std::endl;
    return this->username;
}

std::string Schuler::getPassword()
{
    if (DEBUG) std::cout << "[DEBUG] GETPASSWORD" << std::endl;
    return this->password;
}

void Schuler::setPassword(std::string password)
{
    if (DEBUG) std::cout << "[DEBUG] SETPASSWORD" << std::endl;
    this->password = password;
}

void Schuler::resetPassword()
{
    if (DEBUG) std::cout << "[DEBUG] RESETPASSWORD" << std::endl;
    this->password = std::to_string(geburtsdatum[2]) + "." + std::to_string(geburtsdatum[1]) + "." + std::to_string(geburtsdatum[0]);
}

void Schuler::makeCSV(CSVWriter& csv)
{
    if (DEBUG && !NOMAKECSV) std::cout << "[DEBUG] MAKECSV" << std::endl;
    csv.newRow() << this->nr << this->permissionlevel
                 << this->vorname << this->nachname
                 << this->geburtsdatum[0] << this->geburtsdatum[1]
                 << this->geburtsdatum[2] << this->username << this->password;
}

// standalone functions

// read CSV into schulerliste
void readSchuler(std::vector<Schuler>& schulerliste)
{
    short entry = 0;
    //                                   file, delimiter, first_line_is_header?
    CsvParser* csvparser = CsvParser_new(FILENAME, ",", 0);
    CsvRow* row;

    // CsvParser_destroy_row(header) ; -> causes error in current version
    while ((row = CsvParser_getRow(csvparser)))
    {
        if (DEBUG) std::cout << "[DEBUG] READ " << entry << std::endl;

        char** rowFields = CsvParser_getFields(row);

        schulerliste[entry].init(atoi(rowFields[0]),
                                 atoi(rowFields[1]),
                                 std::string(rowFields[2]),
                                 std::string(rowFields[3]),
                                 atoi(rowFields[4]),
                                 atoi(rowFields[5]),
                                 atoi(rowFields[6]),
                                 std::string(rowFields[7]),
                                 std::string(rowFields[8]));
        ++entry;

        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);
}

// write schulerliste into CSV
void writeSchuler(std::vector<Schuler>& schulerliste)
{
    CSVWriter csv(",");

    if (DEBUG) std::cout << "[DEBUG] WRITE" << std::endl;
    for (long unsigned int i = 0; i < schulerliste.size(); ++i)
    {
        if (schulerliste[i].enabled)
        {
            schulerliste[i].makeCSV(csv);
        }
        csv.writeToFile(FILENAME);
    }
}

// append to schulerliste
void appendSchuler(std::vector<Schuler>& schulerliste,
                   unsigned int permissionlevel,
                   std::string vorname, std::string nachname,
                   short geburtsjahr, short geburtsmonat, short geburtstag)
{
    short entry = 0;
    while (schulerliste[entry].enabled) ++entry;

    if (DEBUG) std::cout << "[DEBUG] APPEND " << entry << std::endl;

    schulerliste[entry].init(schulerliste[entry - 1].getNr() + 1,
                             permissionlevel,
                             vorname,
                             nachname,
                             geburtsjahr, geburtsmonat, geburtstag);
}

void disableSchuler(Schuler& entry)
{
    if (DEBUG) std::cout << "[DEBUG] DISABLE" << std::endl;
    entry.enabled = false;
}