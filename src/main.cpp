#include <iostream>
#include <vector>
#include "schulerparser.h"

int main()
{
    // init vector with Schuler class
    std::vector<Schuler> schulerliste(5);

    // read res/test.csv into schulerliste
    readSchuler(schulerliste);

    // write schulerliste into res/test.csv
    writeSchuler(schulerliste);

    std::cout << "DONE" << std::endl;
}
