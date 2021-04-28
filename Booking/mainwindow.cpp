#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include "QDebug"
#include "ClientAPI.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    QStringList horizontalHeader;
    horizontalHeader.append("ID события");
    horizontalHeader.append("Мастер");
    horizontalHeader.append("Время начала");
    horizontalHeader.append("Продолжительность");

    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableView->setModel(model);
    int k = 0;
    auto companies = dataBase::ClientAPI::listCompanies();
    for (size_t i = 0; i < companies.size(); ++i) {
        auto orders = dataBase::ClientAPI::listVacantOrdersOfCompany(companies[i]);
        for (auto idOfOrder : orders) {
            auto order = dataBase::ClientAPI::getOrderById(idOfOrder);
            item = new QStandardItem(QString(std::to_string(order.id).c_str()));
            model->setItem(k, 0, item);
            auto master = dataBase::ClientAPI::getEmployeeById(order.employeeId);
            item = new QStandardItem(QString(master.fullName.c_str()));
            model->setItem(k, 1, item);
            item = new QStandardItem(QString(std::to_string(order.timeStart).c_str()));
            model->setItem(k, 2, item);
            item = new QStandardItem(QString(std::to_string(order.duration).c_str()));
            model->setItem(k, 3, item);
            ++k;
        }
    }
    ui->tableView->verticalHeader()->hide();
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
            ui->label->setText("Проверьте данные, бронирование не завершено.");
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
        dataBase::Order order = dataBase::ClientAPI::getOrderById(id);
        answer = (order.id == id);
    }
    return answer;
}

