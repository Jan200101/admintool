#include "user.hpp"
#include <algorithm>

/**
 * @file user.cpp
 * @brief Source file for the User class
 *
 * Contains definitions for the User class
 */

/**
 * Empty constructor
 * values are initialized with the init function
 */
User::User()
{
    this->vorname = "";
    this->nachname = "";
    this->username = "";
}

/**
 * @param vorname string
 * @param nachname string
 * @param username string
 *
 * initializes class values
 *
 * if username is empty it is generated with vorname and nachname
 */
void User::init(std::string vorname, std::string nachname, std::string username)
{
    this->vorname = vorname;
    this->nachname = nachname;
    if (username.empty())
    {
        username = vorname + '.' + nachname;
        std::transform(username.begin(), username.end(), username.begin(), ::tolower);
    }
    this->username = username;
}

/**
 * @return string
 * @retval class variable vorname
 */
std::string User::getVorname()
{
    return this->vorname;
}

/**
 * @return string
 * @retval class variable nachname
 */
std::string User::getNachname()
{
    return this->nachname;
}

/**
 * @return string
 * @retval class variable username
 */
std::string User::getUsername()
{
    return this->username;
}