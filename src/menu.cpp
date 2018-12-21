#include "menu.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

menuentry::menuentry(std::string title, std::vector<std::string> menutext, std::vector<func> menufunctions)
{
    if (DEBUG) std::cout << "[DEBUG] MENUENTRY CONSTRUCTER" << std::endl;

    if (menutext.size() != menufunctions.size()) throw std::invalid_argument("menuentry::menuentry vector size does not match");

    this->title = title;
    this->size = menutext.size();
    this->menutext = menutext;
    this->menufunctions = menufunctions;
}

bool menuentry::runfunction(unsigned long entry)
{
    if (DEBUG) std::cout << "[DEBUG] MENUENTRY RUNFUNCTION" << std::endl;

    if (entry >= this->size) return 1;

    this->menufunctions[entry]();
    return 0;
}
bool menuentry::runinput()
{
    if (DEBUG) std::cout << "[DEBUG] MENUENTRY RUNINPUT" << std::endl;

    unsigned long input = 0;

    std::cin >> input;
    --input;
    if (input == (unsigned long)-1) return 1;
    std::cout << std::endl;
    if (this->size >= input) runfunction(input);

    return 0;
}

void menuentry::printtext(std::string exittext)
{
    if (DEBUG) std::cout << "[DEBUG] MENUENTRY PRINTTEXT" << std::endl;

    std::cout << "*** " << this->title << " ***" << std::endl;

    for (long unsigned i = 0; i < this->size; ++i)
    {
        std::cout << i + 1 << std::left << std::setw(2) << '.' << this->menutext[i] << std::endl;
    }
    std::cout << "0. " << exittext << std::endl;
}

void menuentry::printtext()
{
    this->printtext("Zurück");
}