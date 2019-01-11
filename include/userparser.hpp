#ifndef USERPARSER_H
#define USERPARSER_H

#include <string>
#include <vector>
#include "defines.h"
#include "user.hpp"

/**
 * @file userparser.hpp
 * @brief Header for user parsing functions
 *
 * Contains definitions for user parsing functions
 */

std::vector<User> readUser(std::string filename = FILENAME);

void writeUser(std::vector<User>& userliste, std::string filename = FILENAME);

#endif