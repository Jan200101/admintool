#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class menuentry
{
   private:
    std::string title = "";
    unsigned long size = 0;
    std::vector<std::string> menutext;
    std::vector<void (*)()> menufunctions;

   public:
    menuentry(std::string title, std::vector<std::string> menutext, std::vector<void (*)()> menufunctions);
    bool runfunction(unsigned long entry);
    unsigned short runinput();
    void printtext();
};