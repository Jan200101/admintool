#include <iostream>
#include <vector>
#include "schulerparser.h"

int main()
{
    // replace this
    std::vector<Schuler> schulerliste(5);

    readSchuler(schulerliste);

    writeSchuler(schulerliste);

    std::cout << "DONE" << std::endl;
}
