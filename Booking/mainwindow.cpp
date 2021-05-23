#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choicewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->enterPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->enterTelephoneForAuthorizationLineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->pushButton, &QPushButton::clicked, [this]{
        email = ui->enterEmailLineEdit->text().toUtf8().constData();
        telephone = ui->enterTelephoneLineEdit->text().toUtf8().constData();
        name = ui->enterNameLineEdit->text().toUtf8().constData();
        password = ui->enterPasswordLineEdit->text().toUtf8().constData();
        if(isValidTelephone(telephone)) {
            ui->isTelephoneOkLabel->setText("Good");
        } else {
            ui->isTelephoneOkLabel->setText("Bad");
        }
        if(isValidEmail(email)) {
            ui->isEmailOkLabel->setText("Good");
        } else {
            ui->isEmailOkLabel->setText("Bad");
        }
        if(isValidName(name)) {
            ui->isNameOkLabel->setText("Good");
        } else {
            ui->isNameOkLabel->setText("Bad");
        }
        if(isValidPassword(password)) {
            ui->isPasswordOkLabel->setText("Good");
        } else {
            ui->isPasswordOkLabel->setText("Bad");
        }
        if (ui->isEmailOkLabel->text().toStdString() == "Good" &&
                ui->isTelephoneOkLabel->text().toStdString() == "Good" && ui->isNameOkLabel->text().toStdString() == "Good" && ui->isPasswordOkLabel->text().toStdString() == "Good") {
            ui->label->setText("All is ok!");
        } else {
            ui->label->setText("Check information, please, registration is not completed.");
        }
    });

    connect(ui->pushButton_2, &QPushButton::clicked, [this] {
        if (ui->label->text() == "All is ok!") {
            auto client = db::ClientAPI::createClient(telephone, password, name, email);
            ChoiceWindow *w = new ChoiceWindow(client.id, nullptr);
            hide();
            w->show();
        }
    });

    connect(ui->enterButton, &QPushButton::clicked, [this] {
        password = ui->enterPasswordForAuthorizationLineEdit->text().toUtf8().constData();
        telephone = ui->enterTelephoneForAuthorizationLineEdit->text().toUtf8().constData();
        long long id = db::ClientAPI::authorizeClient(telephone, password);
        ChoiceWindow *w = new ChoiceWindow(id, nullptr);
        hide();
        w->show();
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
    unsigned long long posOfFirstAt = str.find_first_of('@'), posOfLastAt = str.find_last_of('@');
    if (posOfFirstAt != posOfLastAt || posOfFirstAt == std::string::npos) {
        return false;
    }

    unsigned long long posOfLastDot = str.find_last_of('.');
    if (posOfLastDot == str.size() - 1 || posOfLastDot == std::string::npos) {
        return false;
    }

    if (posOfLastDot == posOfLastAt + 1) {
        return false;
    }
    return true;
}

bool MainWindow::isValidName(std::string str) {
    return !str.empty();
}

bool MainWindow::isValidPassword(std::string str) {
    return !str.empty();
}
