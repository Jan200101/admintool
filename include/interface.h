#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QTableWidget>
//#include <QTranslator> // TODO add translations

/**
 * @file interface.cpp
 * @brief Header file for the QT UI
 */

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void addRow(const char* forename, const char* surname, const char* nickname);
    void addRow(std::string forename, std::string surname, std::string nickname);
    void setItem(unsigned short count, unsigned short column, const char* text);

   private:
    Ui::MainWindow* ui;
    //QTableWidget* tableWidget;
    //QTranslator m_translator;
};

#endif // INTERFACE_H
