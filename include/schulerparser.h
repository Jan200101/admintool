#include <cstring>
#include <vector>
#include "CSVparser.h"
#include "CSVwriter.cpp"

const char FILENAME[] = "test.csv";

class Schuler
{
   private:
    unsigned int nr;

    std::string vorname;
    std::string nachname;

    std::string geburtsdatum;

    std::string username;
    std::string password; // soon to be hashed with sha512

    //time_t time;

   public:
    void init(int nr, std::string vorname, std::string nachname, std::string geburtsdatum, std::string username, std::string password);

    bool isEmpty();

    int getNr();

    std::string getVorname();
    std::string getNachname();

    std::string getGeburtsdatum();

    std::string getUsername();
    std::string getPassword();

    void makeCSV(CSVWriter &csv);
};

void readSchuler(std::vector<Schuler> &schulerliste);

void writeSchuler(std::vector<Schuler> &schulerliste);