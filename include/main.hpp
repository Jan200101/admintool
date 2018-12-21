#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include "user.hpp"

#ifndef NOMENU
#define NOMENU 0
#endif

void userneuladen();
void userlisten();
void menu();
int main(int argc, char* argv[]);

#endif