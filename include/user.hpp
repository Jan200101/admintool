#ifndef USER_H
#define USER_H

#include <string>
#include "defines.h"

/**
 * @file user.hpp
 * @brief Header for the User class
 *
 * Contains declarations for the User class
 */

/**
 * @brief User class
 *
 * a user class to be used to parse first and last names as well as parse and generate usernames
 */
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