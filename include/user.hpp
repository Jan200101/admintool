#ifndef USER_H
#define USER_H

#include <string>
#include "defines.h"

class User
{
   protected:
    std::string vorname;
    std::string nachname;

    std::string username;

   public:
    User();

    void init(std::string vorname, std::string nachname, std::string username);

    std::string getVorname();
    std::string getNachname();

    std::string getUsername();
};

#endif