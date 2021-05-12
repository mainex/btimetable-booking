#include "choicewindow.h"
#include "ui_choicewindow.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include <QMessageBox>
#include "QDebug"
#include "ClientAPI.h"
#include <iostream>

ChoiceWindow::ChoiceWindow(const int idOfClient, QWidget *parent) :
    QMainWindow(parent),
    clientId(idOfClient),
    ui(new Ui::ChoiceWindow)
{
    ui->setupUi(this);
    auto companies = db::ClientAPI::listCompanies();
    for (size_t i = 0; i < companies.size(); ++i) {
        auto orders = db::ClientAPI::listVacantOrdersOfCompany(companies[i]);
        for (size_t k = 0; k < orders.size(); ++k) {

           auto order = db::ClientAPI::getOrderById(orders[k]);
            auto master = db::ClientAPI::getEmployeeById(order.employeeId);
            std::string str = order.title + ", " + master.fullName + ", c " + std::to_string(order.timeStart) + " до " + std::to_string(order.duration + order.timeStart);
            ui->comboBox->addItem(QString(str.c_str()), QVariant(order.id));
        }
    }

    connect(ui->pushButton, &QPushButton::clicked, [this]{
        auto client = db::ClientAPI::getClientById(clientId);
        auto order = db::ClientAPI::getOrderById(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
        auto master = db::ClientAPI::getEmployeeById(order.employeeId);
        db::ClientAPI::bookOrder(order.id, clientId);
        QMessageBox::information(this, QString("Бронирование прошло успешно!"), QString((client.fullName + ", Вы забронировали: "+ order.title + " (с " + std::to_string(order.timeStart) + " до " + std::to_string(order.duration + order.timeStart) + "), мастер " + master.fullName).c_str()));
        ui->comboBox->clear();
        auto companies = db::ClientAPI::listCompanies();
        for (size_t i = 0; i < companies.size(); ++i) {
            auto orders = db::ClientAPI::listVacantOrdersOfCompany(companies[i]);
            for (size_t k = 0; k < orders.size(); ++k) {
                auto order = db::ClientAPI::getOrderById(orders[k]);
                auto master = db::ClientAPI::getEmployeeById(order.employeeId);
                std::string str = order.title + ", " + master.fullName + ", c " + std::to_string(order.timeStart) + " до " + std::to_string(order.duration + order.timeStart);
                ui->comboBox->addItem(QString(str.c_str()), QVariant(order.id));
            }
        }
    });
}


ChoiceWindow::~ChoiceWindow()
{
    delete ui;
}
