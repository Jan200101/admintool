#include "menu.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG 1

menuentry::menuentry(std::string title, std::vector<std::string> menutext, std::vector<void (*)()> menufunctions)
{
    if (menutext.size() != menufunctions.size()) throw std::invalid_argument("menuentry::menuentry vector size does not match");

    this->title = title;
    this->size = menutext.size();
    this->menutext = menutext;
    this->menufunctions = menufunctions;
}

bool menuentry::runfunction(unsigned long entry)
{
    if (DEBUG) std::cout << "[DEBUG] RUNFUNCTION" << std::endl;

    if (entry >= this->size) return 1;

    this->menufunctions[entry]();
    return 0;
}
unsigned short menuentry::runinput()
{
    if (DEBUG) std::cout << "[DEBUG] RUNINPUT" << std::endl;

    unsigned long input = 0;

    std::cin >> input;
    --input;
    if (input == (unsigned long)-1) return 1;

    if (this->size >= input) runfunction(input);
    return 0;
}

void menuentry::printtext()
{
    if (DEBUG) std::cout << "[DEBUG] PRINTTEXT" << std::endl;

    std::cout << "*** " << this->title << " ***" << std::endl;

    for (long unsigned i = 0; i < this->size; ++i)
    {
        std::cout << i + 1 << std::left << std::setw(2) << '.' << this->menutext[i] << std::endl;
    }
    std::cout << "0. Zurück" << std::endl;
}