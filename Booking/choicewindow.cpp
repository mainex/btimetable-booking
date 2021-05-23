#include "choicewindow.h"
#include "ui_choicewindow.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include <QMessageBox>
#include "QDebug"
#include "ClientAPI.h"
#include <iostream>
#include <time.h>

ChoiceWindow::ChoiceWindow(const int idOfClient, QWidget *parent) :
    QMainWindow(parent),
    clientId(idOfClient),
    ui(new Ui::ChoiceWindow)
{
    ui->setupUi(this);
    auto client = db::ClientAPI::getClientById(clientId);
    ui->label_4->setText(QString(client.fullName.c_str()));
    ui->label_2->setText(QString((client.phoneNumber+ "\n" +client.email).c_str()));
    update();

    connect(ui->pushButton, &QPushButton::clicked, [this](){
        auto client = db::ClientAPI::getClientById(clientId);
        auto order = db::ClientAPI::getOrderById(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
        auto master = db::ClientAPI::getEmployeeById(order.employeeId);
        auto company = db::ClientAPI::getCompanyById(order.companyId);
        db::ClientAPI::bookOrder(order.id, clientId);
        QMessageBox::information(this, QString("Booking completed!"), QString((client.fullName + ", you booked: "+ order.title + " in " + company.name + " (from " + std::to_string(order.timeStart) + " to " + std::to_string(order.duration + order.timeStart) + "), master " + master.fullName).c_str()));
        ui->comboBox->clear();
        update();
    });
}

void ChoiceWindow::showVacantOrders() {
    auto companies = db::ClientAPI::listCompanies();
    for (size_t i = 0; i < companies.size(); ++i) {
        auto orders = db::ClientAPI::listVacantOrdersOfCompany(companies[i]);
        for (size_t k = 0; k < orders.size(); ++k) {
            auto order = db::ClientAPI::getOrderById(orders[k]);
            auto master = db::ClientAPI::getEmployeeById(order.employeeId);
            const time_t timeStart = order.timeStart;
            std::string str = order.title + ", " + master.fullName + ", " + asctime(gmtime(&timeStart));
            str.pop_back();
            ui->comboBox->addItem(QString(str.c_str()), QVariant(order.id));
        }
    }
}

void ChoiceWindow::addOrderToTableView(QStandardItem *item, QStandardItemModel *model, size_t &i, db::Order &order, db::Company &company, db::Employee &master, const time_t& timeStart, const time_t& timeFinish){
    item = new QStandardItem(QString(order.title.c_str()));
    model->setItem(i, 0, item);

    item = new QStandardItem(QString(company.name.c_str()));
    item->setToolTip(QString(company.name.c_str()));
    model->setItem(i, 1, item);

    item = new QStandardItem(QString(master.fullName.c_str()));
    item->setToolTip(QString(master.fullName.c_str()));
    model->setItem(i, 2, item);

    std::string timeStartStr = asctime(gmtime(&timeStart));
    timeStartStr.pop_back();
    item = new QStandardItem(QString(timeStartStr.c_str()));
    model->setItem(i, 3, item);

    std::string timeFinishStr = asctime(gmtime(&timeFinish));
    timeFinishStr.pop_back();
    item = new QStandardItem(QString(timeFinishStr.c_str()));
    model->setItem(i, 4, item);
    ++i;
}

void ChoiceWindow::createTableView(QStandardItemModel* model, QStringList& horizontalHeader, QTableView* tableView, const size_t& size) {
    model->setHorizontalHeaderLabels(horizontalHeader);
    tableView->setModel(model);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int vwidth = tableView->verticalHeader()->width();
    int hwidth = tableView->horizontalHeader()->length();
    int fwidth = tableView->frameWidth() * 2;

    tableView->setFixedWidth(vwidth + hwidth + fwidth);

    int hheight = tableView->horizontalHeader()->height();
    int fheight = tableView->frameWidth() * 2;
    int rheight = tableView->rowHeight(0) * size;

    tableView->setFixedHeight(hheight + fheight + rheight);
}

void ChoiceWindow::update() {
    showVacantOrders();

    auto bookedOrders = db::ClientAPI::listOrdersOfClient(clientId);
    QStandardItemModel *modelFutureOrders = new QStandardItemModel, *modelCompletedOrders = new QStandardItemModel;
    QStandardItem *item;

    QStringList horizontalHeader;

    horizontalHeader.append(QList<QString>({"Event", "Company", "Master", "Start", "Finish"}));

    size_t rowF = 0, rowC = 0;
    for (size_t i = 0; i < bookedOrders.size(); ++i) {
        auto order = db::ClientAPI::getOrderById(bookedOrders[i]);
        auto master = db::ClientAPI::getEmployeeById(order.employeeId);
        auto company = db::ClientAPI::getCompanyById(order.companyId);
        const time_t timeStart = order.timeStart, timeFinish = order.duration + order.timeStart;
        if (timeFinish < time(NULL)){
            addOrderToTableView(item, modelFutureOrders, rowF, order, company, master, timeStart, timeFinish);
        } else {
            addOrderToTableView(item, modelCompletedOrders, rowC, order, company, master, timeStart, timeFinish);
        }
    }

    createTableView(modelFutureOrders, horizontalHeader, ui->futureOrdersTableView, bookedOrders.size());
    createTableView(modelCompletedOrders, horizontalHeader, ui->completedOrdersTableView, bookedOrders.size());
}

ChoiceWindow::~ChoiceWindow()
{
    delete ui;
}
