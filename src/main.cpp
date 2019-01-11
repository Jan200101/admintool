#include "main.hpp"
#include <cstring>
#include <iostream>
#include "menu.hpp"
#include "userparser.hpp"

/**
 * @file main.cpp
 * @brief Source file for various main functions
 *
 * Contains definitions for the various functions, including main
 */

/**
 * @brief global vector of all user objects
 */
std::vector<User> userliste = readUser();

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (!NOMENU && strcmp(argv[1], "menu") == 0) menu();
    }

    return 0;
}

/**
 * @brief main menu function
 */
void menu()
{
    bool running = true;

    std::string title = "User";
    std::string exittext = "Schließen";

    std::vector<std::string> text = {
        "Listen",
        "Neu laden",
    };

    std::vector<void (*)()> func = {(&userlisten),
                                    (&userneuladen)};

    Menuentry menustructure(title, text, func);

    while (running)
    {
        menustructure.printtext(exittext);
        if (menustructure.runinput()) running = false;
    }
}

/**
 * @brief first menu entry
 */
void userlisten()
{
    for (unsigned long y = 0; y < userliste.size(); ++y)
    {
        std::cout
            << userliste[y].getVorname() << ' '
            << userliste[y].getNachname() << ' '
            << userliste[y].getUsername() << ' '
            << '\n'; // TODO make fancy
    }
    if (DEBUG) std::cout << "STACK SIZE " << userliste.size() << std::endl;

    std::cout << std::endl;
}

/**
 * @brief second menu entry
 */
void userneuladen()
{
    userliste = readUser();
}