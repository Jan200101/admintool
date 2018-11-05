#include <cstring>
#include <vector>
#include "CSVparser.h"
#include "CSVwriter.cpp"

const char FILENAME[] = "res/schuler.csv";

class Schuler
{
   private:
    unsigned short nr = 0;
    unsigned short permissionlevel = 0;

    std::string vorname = "";
    std::string nachname = "";

    unsigned short geburtsdatum[3] = {0, 0, 0};

    std::string username = "";
    std::string password = ""; // soon to be hashed with sha256

    //time_t time;

   public:
    bool enabled = false;

    // 1
    void init(unsigned short nr, unsigned short permissionlevel,
              std::string vorname, std::string nachname,
              unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
              std::string username, std::string password);

    // 2
    void init(unsigned short nr, unsigned short permissionlevel,
              std::string vorname, std::string nachname,
              unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
              std::string username, std::string password,
              std::vector<Schuler>& schulerliste);

    // 3
    void init(unsigned short nr, unsigned short permissionlevel,
              std::string vorname, std::string nachname,
              unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
              std::vector<Schuler>& schulerliste);

    unsigned short getNr();
    unsigned short getPermission();

    std::string getVorname();
    std::string getNachname();

    unsigned short* getGeburtsdatum();
    unsigned short getGeburtsjahr();
    unsigned short getGeburtsmonat();
    unsigned short getGeburtstag();

    std::string getUsername();
    std::string getPassword();

    void setPassword(std::string password);
    void resetPassword();
    void hashPassword();
    void hashPassword(std::string& password);
    bool comparePassword(std::string password);

    void makeCSV(CSVWriter& csv);
};

void readSchuler(std::vector<Schuler>& schulerliste);

void writeSchuler(std::vector<Schuler>& schulerliste);

void appendSchuler(std::vector<Schuler>& schulerliste,
                   unsigned int permissionlevel,
                   std::string vorname, std::string nachname,
                   short geburtsjahr, short geburtsmonat, short geburtstag);

void disableSchuler(Schuler& entry);