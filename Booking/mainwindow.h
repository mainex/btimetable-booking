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
    long long id;
    std::string email, name, password, passwordAgain, telephone;
    static void enterId();

    static void enterTelephone();

    static void enterEmail();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
