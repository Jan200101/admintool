#include "menu.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

/**
 * @file menu.cpp
 * @brief Source file for the Menuentry class
 *
 * Contains definitions for the Menuentry class
 */

/**
 * @param title string
 * @param menutext vector of strings
 * @param menufunctions vector of void function pointers
 *
 * title is the header used for the menu
 *
 * menutext is uses for the title of menu entries
 *
 * menufunctions is used to contain the function pointers
 */
Menuentry::Menuentry(std::string title, std::vector<std::string> menutext, std::vector<func> menufunctions)
{
    if (DEBUG) std::cout << "[DEBUG] MENUENTRY CONSTRUCTER" << std::endl;

    if (menutext.size() != menufunctions.size()) throw std::invalid_argument("Menuentry::Menuentry vector size does not match");

    this->title = title;
    this->size = menutext.size();
    this->menutext = menutext;
    this->menufunctions = menufunctions;
}

/**
 * @param entry position of wanted entry as unsigned long
 * @return bool
 * @retval 1 if entry does not exist otherwise 0
 *
 * Calls the function behind the entry number
 */
bool Menuentry::runfunction(unsigned long entry)
{
    if (DEBUG) std::cout << "[DEBUG] MENUENTRY RUNFUNCTION" << std::endl;

    if (entry >= this->size) return 1;

    this->menufunctions[entry]();
    return 0;
}

/**
 * @return bool
 * @retval 1 if input is -1 otherwise 0
 *
 * Reads from stdin and runs runfunction
 */
bool Menuentry::runinput()
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

/**
 * @param exittext string
 *
 * Prints all menu entries and a exit value
 * Default exittext is "Zurück" and defined in defines.h
 */
void Menuentry::printtext(std::string exittext)
{
    if (DEBUG) std::cout << "[DEBUG] MENUENTRY PRINTTEXT" << std::endl;

    std::cout << "*** " << this->title << " ***" << std::endl;

    for (long unsigned i = 0; i < this->size; ++i)
    {
        std::cout << i + 1 << std::left << std::setw(2) << '.' << this->menutext[i] << std::endl;
    }
    std::cout << "0. " << exittext << std::endl;
}