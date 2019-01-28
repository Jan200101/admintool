#include <QCoreApplication>

#include "interface.h"
#include "ui_main.h"
#include "userparser.hpp"

std::vector<User> userliste = readUser();

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->tableWidget = ui->tableWidget;
    //switchTranslator(m_translator, QString("TranslationExample_%1.qm").arg(rLanguage));

    for (unsigned long y = 0; y < userliste.size(); ++y)
    {
        this->addRow(userliste[y].getVorname().c_str(), userliste[y].getNachname().c_str(), userliste[y].getUsername().c_str());
    }

    //this->addRow("forename", "surname", "nickname");
    //this->addRow("HM", "has", "big gay");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRow(const char* forename, const char* surname, const char* nickname)
{
    unsigned short count = tableWidget->rowCount();

    this->tableWidget->setRowCount(count + 1);

    this->setItem(count, 0, forename);
    this->setItem(count, 1, surname);
    this->setItem(count, 2, nickname);
}

void MainWindow::setItem(unsigned short count, unsigned short column, const char* text)
{
    QTableWidgetItem* __qtablewidgetitem = new QTableWidgetItem();

    tableWidget->setItem(count, column, __qtablewidgetitem);
    __qtablewidgetitem->setText(text);
}