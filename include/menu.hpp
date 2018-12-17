#ifndef MENU_H // include guard
#define MENU_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "defines.h"

class menuentry
{
   private:
    std::string title;
    unsigned long size;
    std::vector<std::string> menutext;
    std::vector<void (*)()> menufunctions;

   public:
    menuentry(std::string title, std::vector<std::string> menutext, std::vector<void (*)()> menufunctions);
    bool runfunction(unsigned long entry);
    bool runinput();
    void printtext(std::string exittext);
    void printtext();
};

#endif