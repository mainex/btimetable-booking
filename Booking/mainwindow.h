#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int id;
    std::string email, name, password, passwordAgain, telephone;
    static void enterId();

    static void enterTelephone();

    static void enterEmail();

    static bool isValidName(std::string);

    static bool isValidTelephone(std::string);

    static bool isValidEmail(std::string);

    static bool isValidPassword(std::string, std::string);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
