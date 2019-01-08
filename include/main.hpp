#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include "user.hpp"

/**
 * @file main.hpp
 * @brief Header for various main functions
 *
 * Contains declarations for the various functions, including main
 */

#ifndef NOMENU
#define NOMENU 0
#endif

bool fexists(const char* filename);

int main(int argc, char* argv[]);

#endif