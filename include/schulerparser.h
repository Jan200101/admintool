#include <cstring>
#include <vector>
#include "CSVparser.h"
#include "CSVwriter.cpp"

const char FILENAME[] = "res/schuler.csv";

class Schuler
{
   private:
    unsigned short nr;

    std::string vorname;
    std::string nachname;

    unsigned short geburtsdatum[3];

    std::string username;
    std::string password;

   public:
    bool enabled;

    Schuler();

    // 1
    void init(unsigned short nr,
              std::string vorname, std::string nachname,
              unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
              std::string username, std::string password);

    // 2
    void init(unsigned short nr,
              std::string vorname, std::string nachname,
              unsigned short geburtsjahr, unsigned short geburtsmonat, unsigned short geburtstag,
              std::string username, std::string password,
              std::vector<Schuler>& schulerliste);

    // 3
    void init(unsigned short nr,
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
                   std::string vorname, std::string nachname,
                   short geburtsjahr, short geburtsmonat, short geburtstag);

void disableSchuler(Schuler& entry);