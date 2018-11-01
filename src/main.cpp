#include <iostream>
#include <vector>
#include "schulerparser.h"

#define DEBUG 0

int main()
{
    // init vector with Schuler class
    std::vector<Schuler> schulerliste(50); // 50 should be enough I am not going into dynamic memory allocation for this shit

    // read CSV into schulerliste
    // FILENAME
    // readSchuler(schulerliste);

    appendSchuler(schulerliste, "Avor", "Bnach", 1999, 3, 21);
    writeSchuler(schulerliste);

    if (DEBUG) std::cout << "[DEBUG]DONE" << std::endl;
}
