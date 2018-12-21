#include "main.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include "userparser.hpp"

std::vector<User> userliste;

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

bool fexists(const char* filename)
{
    std::ifstream ifile(filename);
    return (bool)ifile;
}