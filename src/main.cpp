#include <iomanip>
#include <iostream>
#include <vector>
#include "menu.h"
#include "schulerparser.h"

#define DEBUG 0

void menu();
void schulermenu();
void schulerlisten();
void schulerhinzufugen();
void schulerneuladen();
void schulerdeaktivieren();

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

    return 0;
}

void menu()
{
    bool running = true;
    std::string title = "Admintool";
    std::string exittext = "Schließen";

    std::vector<std::string> text = {"Schüler"};

    std::vector<void (*)()> func = {(&schulermenu)};

    menuentry menu(title, text, func);

    while (running)
    {
        menu.printtext(exittext);
        if (menu.runinput()) running = false;
    }
}

void schulermenu()
{
    bool running = true;

    std::string title = "Schuler";

    std::vector<std::string> text = {"Listen",
                                     "Hinzufügen",
                                     "Entfernen",
                                     "Neu laden"};

    std::vector<void (*)()> func = {(&schulerlisten),
                                    (&schulerhinzufugen),
                                    (&schulerneuladen),
                                    (&schulerdeaktivieren)};

    menuentry menu(title, text, func);

    while (running)
    {
        menu.printtext();
        if (menu.runinput()) running = false;
    }
}

void schulerlisten()
{
    for (unsigned long y = 0; y < schulerliste.size(); ++y)
    {
        if (!schulerliste[y].enabled) continue;
        std::cout
            << schulerliste[y].getNr() << ' '
            << schulerliste[y].getVorname() << ' '
            << schulerliste[y].getNachname() << ' '
            << schulerliste[y].getGeburtsdatum()[0] << ' '
            << '\n'; // TODO make fancy
    }
    std::cout << std::endl;
}

void schulerhinzufugen()
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

void schulerneuladen()
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

void schulerdeaktivieren()
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