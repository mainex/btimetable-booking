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
    auto client = db::ClientAPI::getClientById(clientId);

    ui->label_2->setText(QString((client.fullName + "\nid: "+ std::to_string(client.id) + "\n" + client.phoneNumber+ "\n" +client.email).c_str()));

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

    connect(ui->pushButton, &QPushButton::clicked, [this](){
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

    auto bookedOrders = db::ClientAPI::listOrdersOfClient(clientId);
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Событие");
    horizontalHeader.append("Мастер");
    horizontalHeader.append("Начало");
    horizontalHeader.append("Продолжительность");

    model->setHorizontalHeaderLabels(horizontalHeader);

    for (int i = 0; i < bookedOrders.size(); ++i) {
        auto order = db::ClientAPI::getOrderById(bookedOrders[i]);
        auto master = db::ClientAPI::getEmployeeById(order.employeeId);
        item = new QStandardItem(QString(order.title.c_str()));
        model->setItem(i, 0, item);

        item = new QStandardItem(QString(master.fullName.c_str()));
        model->setItem(i, 1, item);

        item = new QStandardItem(QString(std::to_string(order.timeStart).c_str()));
        model->setItem(i, 2, item);

        item = new QStandardItem(QString(std::to_string(order.duration).c_str()));
        model->setItem(i, 3, item);
    }
    ui->tableView->setModel(model);

    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


ChoiceWindow::~ChoiceWindow()
{
    delete ui;
}
