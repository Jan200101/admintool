#ifndef USERPARSER_H
#define USERPARSER_H

#include <string>
#include <vector>
#include "user.hpp"

/**
 * @file userparser.hpp
 * @brief Header for user parsing functions
 *
 * Contains definitions for user parsing functions
 */

std::vector<User> readUser();
std::vector<User> readUser(std::string filename);

void writeUser(std::vector<User>& userliste);
void writeUser(std::vector<User>& userliste, std::string filename);

#endif