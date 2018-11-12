#include "schulerparser.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "CSVparser.h"
#include "CSVwriter.cpp"
#include "sha512.h"

#ifndef DEBUG
#define DEBUG 0
#endif

#define NOMAKECSV 0 // stop makeCSV DEBUG, useful tesing anything
#define NOGETNR 0   // stop getNr DEBUG, useful when appening student entries

// keep this enabled or disabled all the time DO NOT SWITCH AROUND ALL THE TIME
// passwords are hashed with a included sha512 library
#define HASHPASS 1

// Schuler Class

Schuler::Schuler()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER CONSTRUCTER" << std::endl;
    this->vorname = "";
    this->nachname = "";

    this->geburtsdatum[0] = 0;
    this->geburtsdatum[1] = 0;
    this->geburtsdatum[2] = 0;

    this->username = "";
    this->password = "";

    this->enabled = false;
}

// 1
void Schuler::init(unsigned short nr,
                   std::string vorname, std::string nachname,
                   unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
                   std::string username, std::string password)
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER INIT" << std::endl;

    this->enabled = true;

    this->nr = nr;

    this->vorname = vorname;
    this->nachname = nachname;

    this->geburtsdatum[0] = geburtsjahr;
    this->geburtsdatum[1] = geburtsmonat;
    this->geburtsdatum[2] = geburtstag;

    if (username.empty())
    {
        username = vorname + '.' + nachname;
        std::transform(username.begin(), username.end(), username.begin(), ::tolower);
    }
    this->username = username;
    if (password.empty())
    {
        password = std::to_string(geburtstag) + "." + std::to_string(geburtsmonat) + "." + std::to_string(geburtsjahr);
        if (HASHPASS) this->hashPassword(password);
    }
    this->password = password;
}

// 2
void Schuler::init(unsigned short nr,
                   std::string vorname, std::string nachname,
                   unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
                   std::string username, std::string password,
                   std::vector<Schuler>& schulerliste)
{
    unsigned short number = 0;
    std::string name;

    if (username.empty())
    {
        username = vorname + '.' + nachname;
        std::transform(username.begin(), username.end(), username.begin(), ::tolower);
    }

    name = username; // use name as temporary storage

    for (unsigned int i = 0; i < schulerliste.size(); ++i)
    {
        if (schulerliste[i].username == username)
        {
            ++number;
            username = name + std::to_string(number);
            i = 0;
        }
    }

    this->init(nr,
               vorname, nachname,
               geburtsjahr, geburtsmonat, geburtstag,
               username, password);
}

// 3
void Schuler::init(unsigned short nr,
                   std::string vorname, std::string nachname,
                   unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
                   std::vector<Schuler>& schulerliste)
{
    this->init(nr,
               vorname, nachname,
               geburtsjahr, geburtsmonat, geburtstag,
               "", "",
               schulerliste);
}

unsigned short Schuler::getNr()
{
    if (DEBUG && !NOGETNR) std::cout << "[DEBUG] SCHULER GETNR" << std::endl;
    return this->nr;
}

std::string Schuler::getVorname()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER GETVORNAME" << std::endl;
    return this->vorname;
}

std::string Schuler::getNachname()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER GETNACHNAME" << std::endl;
    return this->nachname;
}

unsigned short* Schuler::getGeburtsdatum()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER GETGEBURTSDATUM" << std::endl;
    unsigned short* datum = (unsigned short*)std::malloc(3);
    *datum = *this->geburtsdatum;
    return datum;
}

unsigned short Schuler::getGeburtsjahr()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER GETGEBURTSJAHR" << std::endl;
    return this->geburtsdatum[0];
}

unsigned short Schuler::getGeburtsmonat()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER GETGEBURTSMONAT" << std::endl;
    return this->geburtsdatum[1];
}

unsigned short Schuler::getGeburtstag()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER GETGEBURTSTAG" << std::endl;
    return this->geburtsdatum[2];
}

std::string Schuler::getUsername()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER GETUSERNAME" << std::endl;
    return this->username;
}

std::string Schuler::getPassword()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER GETPASSWORD" << std::endl;
    return this->password;
}

void Schuler::setPassword(std::string password)
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER SETPASSWORD" << std::endl;
    this->password = password;

    if (HASHPASS)
    {
        this->hashPassword();
    }
}

void Schuler::resetPassword()
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER RESETPASSWORD" << std::endl;
    this->password = std::to_string(geburtsdatum[2]) + "." + std::to_string(geburtsdatum[1]) + "." + std::to_string(geburtsdatum[0]);
}

void Schuler::hashPassword()
{
    this->hashPassword(this->password);
}

void Schuler::hashPassword(std::string& password)
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER HASHPASSWORD" << std::endl;
    password = sha512(this->username + password);
}

bool Schuler::comparePassword(std::string password)
{
    if (DEBUG) std::cout << "[DEBUG] SCHULER COMPAREPASSWORD" << std::endl;
    if (HASHPASS) this->hashPassword(password);

    if (password == this->password) return 0;

    return 1;
}

void Schuler::makeCSV(CSVWriter& csv)
{
    if (DEBUG && !NOMAKECSV) std::cout << "[DEBUG] SCHULER MAKECSV" << std::endl;
    csv.newRow() << this->nr << this->vorname << this->nachname
                 << this->geburtsdatum[0] << this->geburtsdatum[1]
                 << this->geburtsdatum[2] << this->username << this->password;
}

// standalone functions

// read CSV into schulerliste
void readSchuler(std::vector<Schuler>& schulerliste)
{
    unsigned short entry = 0;
    //                                   file, delimiter, first_line_is_header?
    CsvParser* csvparser = CsvParser_new(FILENAME, ",", 0);
    CsvRow* row;

    // CsvParser_destroy_row(header) ; -> causes error in current version
    while ((row = CsvParser_getRow(csvparser)))
    {
        if (DEBUG) std::cout << "[DEBUG] SCHULER READ " << entry << std::endl;
        //schulerliste.reserve(schulerliste.size() + 1);
        schulerliste.resize(entry + 1);

        char** rowFields = CsvParser_getFields(row);

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
    writeSchuler(schulerliste);
}

// write schulerliste into CSV
void writeSchuler(std::vector<Schuler>& schulerliste)
{
    CSVWriter csv(",");

    if (DEBUG) std::cout << "[DEBUG] SCHULER WRITE" << std::endl;
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
                   std::string vorname, std::string nachname,
                   short geburtsjahr, short geburtsmonat, short geburtstag)
{
    short entry = 0;
    schulerliste.resize(schulerliste.size() + 1);
    while (schulerliste[entry].enabled) ++entry;

    if (DEBUG) std::cout << "[DEBUG] APPEND " << entry << std::endl;

    schulerliste[entry].init(schulerliste[entry - 1].getNr() + 1,
                             vorname,
                             nachname,
                             geburtsjahr, geburtsmonat, geburtstag,
                             schulerliste);

    if (!schulerliste[schulerliste.size() - 1].enabled) schulerliste.resize(schulerliste.size() - 1);
}

void disableSchuler(Schuler& entry)
{
    if (DEBUG) std::cout << "[DEBUG] DISABLE" << std::endl;
    entry.enabled = false;
}