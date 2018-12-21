#ifndef USERPARSER_H
#define USERPARSER_H

#include <string>
#include <vector>
#include "user.hpp"

std::vector<User> readUser(std::string filename);

void writeUser(std::vector<User>& userliste, std::string filename);

#endif