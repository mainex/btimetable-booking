#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "testdatabase.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    testDataBase.make();
    connect(ui->pushButton, &QPushButton::clicked, [this]{
       ui->idLabel->setText(ui->enterIdLineEdit->text());
       ui->emailLabel->setText(ui->enterEmailLineEdit->text());
       ui->telephoneLabel->setText(ui->enterTelephoneLineEdit->text());
       if(isValidTelephone(ui->enterTelephoneLineEdit->text().toStdString())) {
           ui->isTelephoneOkLabel->setText("Good");
       } else {
           ui->isTelephoneOkLabel->setText("Bad");
       }
       if(isValidEmail(ui->enterEmailLineEdit->text().toStdString())) {
           ui->isEmailOkLabel->setText("Good");
       } else {
           ui->isEmailOkLabel->setText("Bad");
       }
       if(isValidId(ui->enterIdLineEdit->text().toStdString())) {
           ui->isIdOkLabel->setText("Good");
       } else {
           ui->isIdOkLabel->setText("Bad");
       }
       if (ui->isIdOkLabel->text().toStdString() == "Good" &&
               ui->isEmailOkLabel->text().toStdString() == "Good" &&
               ui->isTelephoneOkLabel->text().toStdString() == "Good") {
           ui->label->setText("Данные корректны!");
       } else {
           ui->label->setText("Проверьте введенные данные, бронирование не завершено.");
       }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isValidTelephone(std::string str) {
    if (str.size() != 16) {
        return false;
    }

    if (str[0] != '+' || str[1] != '7') {
        return false;
    }
    int posOfNums[] = {3, 4, 5, 7, 8, 9, 11, 12, 14, 15};
    for (int ind : posOfNums) {
        if (!isdigit(str[ind])) {
            return false;
        }
    }

    int posOfDashes[] = {2, 6, 10, 13};
    for (int ind : posOfDashes) {
        if (str[ind] != '-') {
            return false;
        }
    }

    return true;
}

bool MainWindow::isValidEmail(std::string str) {
    int posOfFirstAt = str.find_first_of('@'), posOfLastAt = str.find_last_of('@');
    if (posOfFirstAt != posOfLastAt || posOfFirstAt == std::string::npos) {
        return false;
    }

    int posOfLastDot = str.find_last_of('.');
    if (posOfLastDot == str.size() - 1 || posOfLastDot == std::string::npos) {
        return false;
    }

    if (posOfLastDot == posOfLastAt + 1) {
        return false;
    }
    return true;
}

bool MainWindow::isValidId(std::string input) {
    bool answer = true;
    for (auto symbol : input) {
        if (symbol < '0' || symbol > '9') {
            answer = false;
        }
    }
    if (answer) {
        int id = stoll(input, nullptr, 10);
        answer = false;
        for (auto comp : testDataBase.companies) {
            if (comp.findOrder(id) != nullptr) {
                answer = true;
            }
        }
    }
   return answer;
}
