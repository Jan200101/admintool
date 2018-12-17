#include "main.hpp"
#include <iostream>
#include <string>
#include "menu.hpp"
#include "userparser.hpp"

int main()
{
    // read CSV into schulerliste
    // FILENAME defiend in schulerparser.h
    //         Schuler vector
    readUser(userliste);

    menu();

    return 0;
}

void menu()
{
    bool running = true;

    std::string title = "User";

    std::vector<std::string> text = {
        "Listen",
        "Neu laden",
    };

    std::vector<void (*)()> func = {(&userlisten),
                                    (&userneuladen)};

    menuentry menu(title, text, func);

    while (running)
    {
        menu.printtext();
        if (menu.runinput()) running = false;
    }
}

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

void userneuladen()
{
    readUser(userliste);
}