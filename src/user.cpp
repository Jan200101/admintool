#include "user.hpp"
#include <algorithm>

User::User()
{
    this->vorname = "";
    this->nachname = "";
    this->username = "";
}

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

std::string User::getVorname()
{
    return this->vorname;
}

std::string User::getNachname()
{
    return this->nachname;
}

std::string User::getUsername()
{
    return this->username;
}