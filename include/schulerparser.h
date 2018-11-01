#include <cstring>
#include <vector>
#include "CSVparser.h"
#include "CSVwriter.cpp"

const char FILENAME[] = "res/test.csv";

class Schuler
{
   private:
    unsigned int nr;

    std::string vorname;
    std::string nachname;

    short geburtsdatum[3] = {0, 0, 0};

    std::string username;
    std::string password; // soon to be hashed with sha512

    //time_t time;

   public:
    bool enabled = false;

    void init(int nr, std::string vorname, std::string nachname,
              short geburtsjahr, short geburtsmonat, short geburtstag,
              std::string username, std::string password);

    void init(int nr, std::string vorname, std::string nachname,
              short geburtsjahr, short geburtsmonat, short geburtstag);

    int getNr();

    std::string getVorname();
    std::string getNachname();

    short *getGeburtsdatum();

    std::string getUsername();
    std::string getPassword();

    void makeCSV(CSVWriter &csv);
};

void readSchuler(std::vector<Schuler> &schulerliste);

void writeSchuler(std::vector<Schuler> &schulerliste);

void appendSchuler(std::vector<Schuler> &schulerliste,
                   std::string vorname, std::string nachname,
                   short geburtsjahr, short geburtsmonat, short geburtstag);