#include <iostream>
#include <vector>
#include "schulerparser.h"

#define DEBUG 0

int main()
{
    // init vector with Schuler class
    std::vector<Schuler> schulerliste(50); // 50 should be enough I am not going into dynamic memory allocation for this shit

    // read CSV into schulerliste
    // FILENAME defiend in schulerparser.h
    //         Schuler vector
    readSchuler(schulerliste);

    // add entry to schulerlist
    //    Schuler array, permission, Name, LastName, Birth Y/M/D
    appendSchuler(schulerliste, 0, "Avor", "Bnach", 1999, 3, 21);

    // write schulerliste onto CSV
    //          Schuler vector
    writeSchuler(schulerliste);

    if (DEBUG) std::cout << "[DEBUG]DONE" << std::endl;
}
