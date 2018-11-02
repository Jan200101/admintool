#include <iomanip>
#include <iostream>
#include <vector>
#include "schulerparser.h"

#define DEBUG 0

void menu();
void submenu1();
void option11();
void option12();
void option13();
void option14();

// init vector in the global space with Schuler class
std::vector<Schuler> schulerliste(50); // 50 should be enough I am not going into dynamic memory allocation for this shit

// global char to store input into
char input;

int main()
{
    // read CSV into schulerliste
    // FILENAME defiend in schulerparser.h
    //         Schuler vector
    readSchuler(schulerliste);
    menu();
}

void menu()
{
    bool running = true;

    while (running)
    {
        std::cout << "*** Admintool ***\n"
                  << "1 - Schüler\n"
                  << "0 - Schließen\n";

        std::cin >> input;

        std::cout << std::endl; // flush stream

        switch (input)
        {
            case '0':
                running = false;
                break;

            case '1':
                submenu1();
                break;
        }
    }
}

void submenu1()
{
    bool running = true;

    while (running)
    {
        std::cout << "*** Schuler ***\n"
                  << "1 - Listen\n"
                  << "2 - Hinzufügen\n"
                  << "3 - Entfernen\n"
                  << "4 - Neu laden\n"
                  << "0 - Zurück\n";

        std::cin >> input;

        std::cout << std::endl; // flush stream

        switch (input)
        {
            case '0':
                running = false;
                break;

            case '1':
                option11();
                break;

            case '2':
                option12();
                break;

            case '3':
                option13();
                break;

            case '4':
                option14();
        }
    }
}

void option11()
{
    for (unsigned long y = 0; y < schulerliste.size(); ++y)
    {
        if (!schulerliste[y].enabled) continue;
        std::cout
            << schulerliste[y].getNr() << '\n'
            << schulerliste[y].getVorname() << '\n'
            << schulerliste[y].getNachname() << '\n'
            << schulerliste[y].getGeburtsdatum()[0] << '\n'
            << '\n'; // TODO make fancy
    }
    std::cout << std::endl;
}

void option12()
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

void option13()
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

void option14()
{
    for (unsigned long i = 0; i < schulerliste.size(); ++i)
    {
        if (schulerliste[i].enabled) disableSchuler(schulerliste[i]);
    }
    readSchuler(schulerliste);
}

/*
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
*/