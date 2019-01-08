#include "main.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include "userparser.hpp"

/**
 * @file main.cpp
 * @brief Source file for various main functions
 *
 * Contains definitions for the various functions, including main
 */

/**
 * @name userliste
 * @brief global vector of all user objects
 */
std::vector<User> userliste;

/**
 * @name main
 */
int main(int argc, char* argv[])
{
    if (argc > 1 && fexists(argv[1]))
    {
        try
        {
            userliste = readUser(argv[1]);
        }
        catch (...)
        {
            std::cout << "File is not a proper CSV" << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
    }

    return 0;
}

/**
 * @param filename constant char pointer
 *
 * checks if there is a file under the path
 */
bool fexists(const char* filename)
{
    std::ifstream ifile(filename);
    return (bool)ifile;
}