#include "main.h"
#include "interface.h"

#include <QApplication>

/**
 * @file main.cpp
 * @brief Source file for the main funcion
 */

/**
 * @brief main function
 */
int main(int argc, char* argv[])
{
    QApplication a(argc, argv); //setup QApplication before calling QMainWindow class
    MainWindow w;               // class that inherits from QMainWindow
    w.show();

    return a.exec();
}
