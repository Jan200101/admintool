#include <QCoreApplication>
#include <string>

#include "interface.h"
#include "ui_main.h"
#include "userparser.hpp"

/**
 * @file interface.cpp
 * @brief Source file for the QT UI
 *
 * UI is converted during compilation this contains the row mechanisms
 */

/**
 * @brief global vector of all user objects
 */
std::vector<User> userliste = readUser();

/**
 * @brief class constructor
 *
 * sets up a new instance of the MainWindow class from the converted UI
 */
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //switchTranslator(m_translator, QString("TranslationExample_%1.qm").arg(rLanguage));

    for (unsigned long y = 0; y < userliste.size(); ++y)
    {
        this->addRow(userliste[y].getVorname(), userliste[y].getNachname(), userliste[y].getUsername());
    }
}

/**
 * @brief class destructor
 *
 * cleans up leftovers
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief adds a row to the table
 * @param forename text for the forename column
 * @param surname text for the surname column
 * @param nickname text for the nickname column
 */
void MainWindow::addRow(const char* forename, const char* surname, const char* nickname)
{
    unsigned short count = ui->tableWidget->rowCount();

    ui->tableWidget->setRowCount(count + 1);

    this->setItem(count, 0, forename);
    this->setItem(count, 1, surname);
    this->setItem(count, 2, nickname);
}

void MainWindow::addRow(std::string forename, std::string surname, std::string nickname)
{
    this->addRow(forename.c_str(), surname.c_str(), nickname.c_str());
}

/**
 * @brief sets an items text value
 */
void MainWindow::setItem(unsigned short count, unsigned short column, const char* text)
{
    QTableWidgetItem* __qtablewidgetitem = new QTableWidgetItem();

    ui->tableWidget->setItem(count, column, __qtablewidgetitem);
    __qtablewidgetitem->setText(text);
}