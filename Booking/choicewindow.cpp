#include "choicewindow.h"
#include "ui_choicewindow.h"
#include <QMessageBox>

ChoiceWindow::ChoiceWindow(const int idOfClient, QWidget *parent) :
    QMainWindow(parent),
    clientId(idOfClient),
    ui(new Ui::ChoiceWindow)
{
    try{
        ui->setupUi(this);
        auto client = db::ClientAPI::getClientById(clientId);
        ui->label_4->setText(QString(client.fullName.c_str()));
        ui->label_2->setText(QString((client.phoneNumber+ "\n" +client.email).c_str()));
        update();

        connect(ui->bookButton, &QPushButton::clicked, [this](){
            auto client = db::ClientAPI::getClientById(clientId);
            auto order = db::ClientAPI::getOrderById(ui->orderComboBox->itemData(ui->orderComboBox->currentIndex()).toLongLong());
            auto master = db::ClientAPI::getEmployeeById(order.employeeId);
            auto company = db::ClientAPI::getCompanyById(order.companyId);
            db::ClientAPI::bookOrder(order.id, clientId);
            QMessageBox::information(this, QString("Booking completed!"), QString((client.fullName + ", you booked: " + to_string(order, master, company)).c_str()));
            update();
        });

        connect(ui->futureOrdersTableView, &QTableView::doubleClicked, [&](const QModelIndex& index){
            if (index.column() == 5){
                long long id = atoll(ui->futureOrdersTableView->model()->data(ui->futureOrdersTableView->model()->index(index.row(), 6)).toString().toUtf8().constData());
                auto order = db::ClientAPI::getOrderById(id);
                auto master = db::ClientAPI::getEmployeeById(order.employeeId);
                auto company = db::ClientAPI::getCompanyById(order.companyId);
                QMessageBox msgBox;
                msgBox.setText("Are you sure?");
                msgBox.setInformativeText(("Do you want to cancel this order: " + to_string(order, master, company)).c_str());
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);
                int res = msgBox.exec();
                if (res == QMessageBox::Yes) {
                    db::ClientAPI::cancelOrder(id);
                    update();
                }
            }
        });

        connect(ui->applyFiltersButton, &QPushButton::clicked, [this](){

            update();
        });
    }
    catch(...) {
        errorProcessing();
    }
}

void ChoiceWindow::showVacantOrders() {
    try{
        auto companies = db::ClientAPI::listCompanies();
        for (size_t i = 0; i < companies.size(); ++i) {
            auto company = db::ClientAPI::getCompanyById(companies[i]);
            auto orders = db::ClientAPI::listVacantOrdersOfCompany(company.id);
            for (size_t k = 0; k < orders.size(); ++k) {
                auto order = db::ClientAPI::getOrderById(orders[k]);
                auto master = db::ClientAPI::getEmployeeById(order.employeeId);
                std::string str = to_string(order, master, company);
                ui->orderComboBox->addItem(QString(str.c_str()), QVariant(order.id));
            }
        }
    }
    catch(...)
    {
        errorProcessing();
    }
}

void ChoiceWindow::showCompanies() {
    try{
        auto companies = db::ClientAPI::listCompanies();
        ui->companyComboBox->addItem(QString("All"), QVariant(-1));
        for (size_t i = 0; i < companies.size(); ++i) {
            auto company = db::ClientAPI::getCompanyById(companies[i]);
            std::string str = company.name;
            ui->companyComboBox->addItem(QString(str.c_str()), QVariant(company.id));
        }
    }
    catch(...)
    {
        errorProcessing();
    }
}

void ChoiceWindow::showMasters() {
    try{
        auto companies = db::ClientAPI::listCompanies();
        ui->masterComboBox->addItem(QString("All"), QVariant(-1));
        for (size_t i = 0; i < companies.size(); ++i) {
            auto masters = db::ClientAPI::listEmployeesOfCompany(companies[i]);
            for (size_t k = 0; k < masters.size(); ++k) {
                auto master = db::ClientAPI::getEmployeeById(masters[k]);
                std::string str = master.fullName;
                ui->masterComboBox->addItem(QString(str.c_str()), QVariant(master.id));
            }
        }
    }
    catch(...)
    {
        errorProcessing();
    }
}

void ChoiceWindow::addOrderToTableView(QStandardItem *item, QStandardItemModel *model, int &i, db::Order &order, db::Company &company, db::Employee &master, const time_t& timeStart, const time_t& timeFinish, bool comments = false){
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

    if (comments){
        item = new QStandardItem(QString("Leave a comment"));
        model->setItem(i, 5, item);
    } else {
        item = new QStandardItem(QString("Cancel"));
        model->setItem(i, 5, item);
        item = new QStandardItem(QString(std::to_string(order.id).c_str()));
        model->setItem(i, 6, item);
    }

    if (false){
        for (int j = 0; j < 5 + comments; ++j){
            model->setData(model->index(i, j), QColor(Qt::gray), Qt::BackgroundRole);
        }
    }
    ++i;
}

void ChoiceWindow::createTableView(QStandardItemModel* model, QStringList& horizontalHeader, QTableView* tableView, const int& size) {
    model->setHorizontalHeaderLabels(horizontalHeader);
    tableView->setModel(model);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);

    int vwidth = tableView->verticalHeader()->width();
    int hwidth = tableView->horizontalHeader()->length();
    int fwidth = tableView->frameWidth() * 2;

    tableView->setFixedWidth(vwidth + hwidth + fwidth);

    int hheight = tableView->horizontalHeader()->height();
    int fheight = tableView->frameWidth() * 2;
    int rheight = tableView->rowHeight(0) * size;

    tableView->setFixedHeight(hheight + fheight + rheight);
}

void ChoiceWindow::globalUpdate() {
    update();
}

void ChoiceWindow::update() {
    try{
        ui->orderComboBox->clear();
        showVacantOrders();

        ui->masterComboBox->clear();
        showMasters();

        ui->companyComboBox->clear();
        showCompanies();

        auto bookedOrders = db::ClientAPI::listOrdersOfClient(clientId);
        QStandardItemModel *modelFutureOrders = new QStandardItemModel, *modelCompletedOrders = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;

        int rowF = 0, rowC = 0;
        for (size_t i = 0; i < bookedOrders.size(); ++i) {
            auto order = db::ClientAPI::getOrderById(bookedOrders[i]);
            auto master = db::ClientAPI::getEmployeeById(order.employeeId);
            auto company = db::ClientAPI::getCompanyById(order.companyId);
            const time_t timeStart = order.timeStart, timeFinish = order.duration + order.timeStart;
            if (timeFinish < time(NULL)){
                addOrderToTableView(item, modelFutureOrders, rowF, order, company, master, timeStart, timeFinish);
            } else {
                addOrderToTableView(item, modelCompletedOrders, rowC, order, company, master, timeStart, timeFinish, true);
            }
        }
        horizontalHeader.append(QList<QString>({"Event", "Company", "Master", "Start", "Finish", "Status"}));
        createTableView(modelFutureOrders, horizontalHeader, ui->futureOrdersTableView, bookedOrders.size());
        ui->futureOrdersTableView->setColumnHidden(6, true);
        horizontalHeader.pop_back();
        horizontalHeader.append("My comments");
        createTableView(modelCompletedOrders, horizontalHeader, ui->completedOrdersTableView, bookedOrders.size());
    }
    catch(...){
        errorProcessing();
    }
}

std::string ChoiceWindow::to_string(db::Order &order, db::Employee& master, db::Company& company) {
    const time_t timeStart = order.timeStart, timeFinish = order.timeStart + order.duration;
    std::string timeS = asctime(gmtime(&timeStart)), timeF = asctime(gmtime(&timeFinish));
    timeS.pop_back();
    timeF.pop_back();
    return order.title + " in " + company.name + " (from " + timeS + " to " + timeF + "), master " + master.fullName;
}

void ChoiceWindow::errorProcessing(){
    QMessageBox::information(this, QString("Error!"), QString("Error"));
}
ChoiceWindow::~ChoiceWindow()
{
    delete ui;
}
