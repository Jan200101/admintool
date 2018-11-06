#include "menu.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG 0

menuentry::menuentry(std::string title, std::vector<std::string> menutext, std::vector<void (*)()> menufunctions)
{
    if (DEBUG) std::cout << "[DEBUG] MENUENTRY CONSTRUCTER" << std::endl;

    if (menutext.capacity() != menufunctions.capacity()) throw std::invalid_argument("menuentry::menuentry vector size does not match");

    this->title = title;
    this->size = menutext.capacity();
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