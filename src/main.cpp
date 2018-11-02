#include <iomanip>
#include <iostream>
#include <vector>
#include "schulerparser.h"

#define DEBUG 0

void menu(std::vector<Schuler> &schulerliste);
void submenu1(std::vector<Schuler> &schulerliste, char &input);
void submenu11(std::vector<Schuler> &schulerliste);
void submenu12(std::vector<Schuler> &schulerliste);
void submenu13(std::vector<Schuler> &schulerliste);
void submenu14(std::vector<Schuler> &schulerliste);

int main()
{
    // init vector with Schuler class
    std::vector<Schuler> schulerliste(50); // 50 should be enough I am not going into dynamic memory allocation for this shit

    // read CSV into schulerliste
    // FILENAME defiend in schulerparser.h
    //         Schuler vector
    readSchuler(schulerliste);

    menu(schulerliste);
}

void menu(std::vector<Schuler> &schulerliste)
{
    char input;
    bool running = true;

    while (running)
    {
        std::cout << "*** Admintool ***\n"
                  << "1 - Schuler\n"
                  << "0 - Exit\n";

        std::cin >> input;

        std::cout << std::endl; // flush stream

        switch (input)
        {
            case 48:
                running = false;
                break;

            case 49:
                submenu1(schulerliste, input);
                break;

            default:
                std::cout << (int)input << std::endl;
        }
    }
}

void submenu1(std::vector<Schuler> &schulerliste, char &input)
{
    bool running = true;

    while (running)
    {
        std::cout << "*** Schuler ***\n"
                  << "1 - Listen\n"
                  << "2 - Hinzufügen\n"
                  << "3 - Entfernen\n"
                  << "4 - Neu laden\n"
                  << "0 - Zuruck\n";

        std::cin >> input;

        std::cout << std::endl; // flush stream

        switch (input)
        {
            case 48:
                running = false;
                break;

            case 49:
                submenu11(schulerliste);
                break;

            case 50:
                submenu12(schulerliste);
                break;

            case 51:
                submenu13(schulerliste);
                break;

            case 52:
                submenu14(schulerliste);
        }
    }
}

void submenu11(std::vector<Schuler> &schulerliste)
{
    for (unsigned long y = 0; y < schulerliste.size(); ++y)
    {
        if (!schulerliste[y].enabled) continue;
        std::cout
            << schulerliste[y].getNr() << '\n'
            << schulerliste[y].getVorname() << '\n'
            << schulerliste[y].getNachname() << '\n'
            << schulerliste[y].getGeburtsjahr() << '\n'
            << '\n'; // TODO make fancy
    }
    std::cout << std::endl;
}

void submenu12(std::vector<Schuler> &schulerliste)
{
    std::string vorname;
    std::string nachname;
    unsigned int geburtsjahr;
    unsigned int geburtsmonat;
    unsigned int geburtstag;

    std::cout << "Vorname" << std::endl;
    std::cin >> vorname;

    std::cout << "Nachname" << std::endl;
    std::cin >> nachname;

    std::cout << "Jahr" << std::endl;
    std::cin >> geburtsjahr;

    std::cout << "Monat" << std::endl;
    std::cin >> geburtsmonat;

    std::cout << "Tag" << std::endl;
    std::cin >> geburtstag;

    appendSchuler(schulerliste, 0, vorname, nachname, geburtsjahr, geburtsmonat, geburtstag);

    writeSchuler(schulerliste);
}

void submenu13(std::vector<Schuler> &schulerliste)
{
    bool change = false;
    unsigned short input = 0;
    Schuler select;

    std::cout << "Welche Schuler Nr soll entfernt werden?" << std::endl;

    std::cin >> input;

    for (unsigned long i = 0; i < schulerliste.size(); ++i)
    {
        if (input == schulerliste[i].getNr())
        {
            disableSchuler(schulerliste[i]);
            std::cout << schulerliste[i].getVorname() << " entfernt" << std::endl;
            change = true;
        }
    }

    if (change) writeSchuler(schulerliste);
}

void submenu14(std::vector<Schuler> &schulerliste)
{
    for (unsigned long i = 0; i < schulerliste.size(); ++i)
    {
        if (schulerliste[i].enabled) disableSchuler(schulerliste[i]);
    }
    readSchuler(schulerliste);
}

void example()
{
    // init vector with Schuler class
    std::vector<Schuler> schulerliste(50); // 50 should be enough I am not going into dynamic memory allocation for this shit

    // read CSV into schulerliste
    // FILENAME defiend in schulerparser.h
    //         Schuler vector
    readSchuler(schulerliste);

    // add entry to schulerlist
    //     Schuler vector, permission, Name, LastName, Birth Y/M/D
    appendSchuler(schulerliste, 0, "Avor", "Bnach", 1999, 3, 21);

    // disable Schuler
    // DISABLING THE LAST USER MAKES THAT USER ID REUSABLE
    //             Schuler
    disableSchuler(schulerliste[0]);

    // write schulerliste onto CSV
    //          Schuler vector
    writeSchuler(schulerliste);

    if (DEBUG) std::cout << "[DEBUG]DONE" << std::endl;
}
