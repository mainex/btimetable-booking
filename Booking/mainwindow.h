#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "testdatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    long long id = -1;
        std::string email, telephone;

        void enterId();
        dataBase::TestDataBase testDataBase = dataBase::TestDataBase();
        void enterTelephone();

        void enterEmail();

        bool isValidId(std::string);

        static bool isValidTelephone(std::string);

        static bool isValidEmail(std::string);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
