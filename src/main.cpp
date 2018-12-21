#include "main.hpp"
#include <cstring>
#include <iostream>
#include "menu.hpp"
#include "userparser.hpp"

std::vector<User> userliste = readUser();

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        if (!NOMENU && strcmp(argv[1], "menu") == 0) menu();
    }

    return 0;
}

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

    menuentry menu(title, text, func);

    while (running)
    {
        menu.printtext(exittext);
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
    userliste = readUser();
}