#ifndef MENU_H // include guard
#define MENU_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "defines.h"

/**
 * @file menu.hpp
 * @brief Header for the Menuentry class
 *
 * Contains declarations for the Menuentry class
 */

/**
 * @name func
 * sets typedef for a void function pointer
 */
typedef void (*func)();

/**
 * @brief menu generation class
 *
 * a menu structure class made for the console
 * allows for dynamic allocation of menu entries
 */
class Menuentry
{
   private:
    std::string title;
    unsigned long size;
    std::vector<std::string> menutext;
    std::vector<func> menufunctions;

   public:
    Menuentry(std::string title, std::vector<std::string> menutext, std::vector<func> menufunctions);
    bool runfunction(unsigned long entry);
    bool runinput();
    void printtext();
    void printtext(std::string exittext);
};

#endif