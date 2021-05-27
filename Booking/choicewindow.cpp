#include "choicewindow.h"
#include "ui_choicewindow.h"
#include "mainwindow.h"
#include <QMessageBox>

ChoiceWindow::ChoiceWindow(const std::string tokenOfClient, QWidget *parent) :
    QMainWindow(parent),
    clientToken(tokenOfClient),
    ui(new Ui::ChoiceWindow)
{
    try{
        ui->setupUi(this);
        auto client = db::ClientAPI::getClient(clientToken);
        ui->label_4->setText(QString(client.fullName.c_str()));
        ui->label_2->setText(QString((client.phoneNumber + "\n" + client.email).c_str()));
        modelFutureOrders = new QStandardItemModel, modelCompletedOrders = new QStandardItemModel;
        rowF = 0, rowC = 0;

        globalUpdate();

        connect(ui->bookButton, &QPushButton::clicked, [this](){
            try{
                auto client = db::ClientAPI::getClient(clientToken);
                auto order = db::ClientAPI::getOrderById(clientToken, ui->orderComboBox->itemData(ui->orderComboBox->currentIndex()).toLongLong());
                auto master = db::ClientAPI::getEmployeeById(order.employeeId);
                auto company = db::ClientAPI::getCompanyById(order.companyId);
                const time_t timeStart = order.timeStart, timeFinish = order.duration + order.timeStart;
                db::ClientAPI::bookOrder(clientToken, order.id);
                QMessageBox::information(this, QString("Booking completed!"), QString((client.fullName + ", you booked: " + to_string(order, master, company)).c_str()));
                ui->orderComboBox->removeItem(ui->orderComboBox->currentIndex());
                if (timeFinish < time(0)) {
                    addOrderToTableView(item, modelCompletedOrders, rowC, order, company, master, timeStart, timeFinish, true);
                } else {
                    addOrderToTableView(item, modelFutureOrders, rowF, order, company, master, timeStart, timeFinish, false);
                }
            }
            catch(...){
                QMessageBox::information(this, QString("Error!"), QString("Error"));
            }
        });

        connect(ui->applyFiltersButton, &QPushButton::clicked, [this](){
            try{
                auto companyId = ui->companyComboBox->itemData(ui->companyComboBox->currentIndex()).toLongLong();
                auto masterId = ui->masterComboBox->itemData(ui->masterComboBox->currentIndex()).toLongLong();
                auto date = ui->dateEdit->time().toString();
                showVacantOrders(companyId, masterId);
                if (companyId > 0) {
                    auto company = db::ClientAPI::getCompanyById(companyId);
                    if (company.rating >0) {
                        ui->companyRatingLabel->setText(QString(("Rating: " + std::to_string(company.rating)).c_str()));
                    } else {
                        ui->companyRatingLabel->setText(QString("No rating yet"));
                    }
                } else {
                    ui->companyRatingLabel->setText(QString(""));
                }
                if (masterId > 0) {
                    auto master = db::ClientAPI::getEmployeeById(masterId);
                    if (master.rating >0) {
                        ui->masterRatingLabel->setText(QString(("Rating: " + std::to_string(master.rating)).c_str()));
                    } else {
                        ui->masterRatingLabel->setText(QString("No rating yet"));
                    }
                } else {
                    ui->masterRatingLabel->setText(QString(""));
                }
            }
            catch(...){
                QMessageBox::information(this, QString("Error!"), QString("Error"));
            }
        });

        connect(ui->futureOrdersTableView, &QTableView::doubleClicked, [&](const QModelIndex& index){
            if (index.column() == 5){
                long long id = atoll(ui->futureOrdersTableView->model()->data(ui->futureOrdersTableView->model()->index(index.row(), 6)).toString().toUtf8().constData());
                try{
                    auto order = db::ClientAPI::getOrderById(clientToken, id);
                    auto master = db::ClientAPI::getEmployeeById(order.employeeId);
                    auto company = db::ClientAPI::getCompanyById(order.companyId);
                    QMessageBox msgBox;
                    msgBox.setText("Are you sure?");
                    msgBox.setInformativeText(("Do you want to cancel this order: " + to_string(order, master, company)).c_str());
                    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    msgBox.setDefaultButton(QMessageBox::Yes);
                    int res = msgBox.exec();
                    if (res == QMessageBox::Yes) {
                        ui->futureOrdersTableView->model()->removeRow(ui->futureOrdersTableView->currentIndex().row());
                        db::ClientAPI::cancelOrder(clientToken, id);
                    }
                }
                catch(...){
                    QMessageBox::information(this, QString("Error!"), QString("Error"));
                }
            }
        });

        connect(ui->completedOrdersTableView, &QTableView::doubleClicked, [&](const QModelIndex& index){
            if (index.column() == 5){
                long long id = atoll(ui->completedOrdersTableView->model()->data(ui->completedOrdersTableView->model()->index(index.row(), 6)).toString().toUtf8().constData());
                try{
                    auto order = db::ClientAPI::getOrderById(clientToken, id);
                    if (order.rating < 1){
                        auto master = db::ClientAPI::getEmployeeById(order.employeeId);
                        auto company = db::ClientAPI::getCompanyById(order.companyId);
                        QMessageBox msgBox;
                        msgBox.setInformativeText(("Rate this order: " + to_string(order, master, company)).c_str());
                        msgBox.addButton(tr("1"), QMessageBox::NoRole);
                        msgBox.addButton(tr("2"), QMessageBox::NoRole);
                        msgBox.addButton(tr("3"), QMessageBox::NoRole);
                        msgBox.addButton(tr("4"), QMessageBox::NoRole);
                        msgBox.addButton(tr("5"), QMessageBox::NoRole);
                        msgBox.exec();
                        int rating = atoi(msgBox.clickedButton()->text().toStdString().c_str());
                        db::ClientAPI::rateOrder(clientToken, id, rating);
                        item = new QStandardItem(QString(std::to_string(rating).c_str()));
                        modelCompletedOrders->setItem(index.row(), index.column(), item);
                        ui->completedOrdersTableView->setModel(modelCompletedOrders);
                    }
                }
                catch(...){
                    QMessageBox::information(this, QString("Error!"), QString("Error"));
                }
            }
        });

        connect(ui->actionExit, &QAction::triggered, [this](){
            close();
        });

        connect(ui->actionLogOut, &QAction::triggered, [this](){
            MainWindow *w = new MainWindow;
            close();
            w->show();
        });
        
    }
    catch(...) {
        errorProcessing();
    }
}

void ChoiceWindow::showVacantOrders(long long companyId, long long employeeId, long long leastTimeStart, long long leastDuration, db::sortParam sortBy, bool reversed){
    try{
        ui->orderComboBox->clear();
        std::vector<long long> companies;
        try{
            if(companyId == -1){
                companies = db::ClientAPI::listCompanies();
            } else {
                companies.push_back(companyId);
            }
            for (size_t i = 0; i < companies.size(); ++i) {
                auto company = db::ClientAPI::getCompanyById(companies[i]);
                std::vector<long long> orders;
                if (employeeId == -1) {
                    for (auto master : db::ClientAPI::listEmployeesOfCompany(companies[i])){
                        orders = db::ClientAPI::listOrders(companies[i], master, db::Order::vacant, leastTimeStart, leastDuration, sortBy, reversed);
                        for (size_t k = 0; k < orders.size(); ++k) {
                            auto order = db::ClientAPI::getOrderById(clientToken, orders[k]);
                            auto master = db::ClientAPI::getEmployeeById(order.employeeId);
                            std::string str = to_string(order, master, company);
                            ui->orderComboBox->addItem(QString(str.c_str()), QVariant(order.id));
                        }
                    }
                } else {
                    orders = db::ClientAPI::listOrders(companies[i], employeeId, db::Order::vacant, leastTimeStart, leastDuration, sortBy, reversed);
                    for (size_t k = 0; k < orders.size(); ++k) {
                        auto order = db::ClientAPI::getOrderById(clientToken, orders[k]);
                        auto master = db::ClientAPI::getEmployeeById(order.employeeId);
                        std::string str = to_string(order, master, company);
                        ui->orderComboBox->addItem(QString(str.c_str()), QVariant(order.id));
                    }
                }
            }
        }
        catch(...){
            QMessageBox::information(this, QString("Error!"), QString("Error"));
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
    }\
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
    if (company.rating > 0) {
        item->setToolTip(QString(std::to_string(company.rating).c_str()));
    } else {
        item->setToolTip(QString("No rating yet"));
    }
    model->setItem(i, 1, item);

    item = new QStandardItem(QString(master.fullName.c_str()));
    if (master.rating > 0) {
        item->setToolTip(QString(std::to_string(master.rating).c_str()));
    } else {
        item->setToolTip(QString("No rating yet"));
    }
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
        if(order.rating < 1) {
            item = new QStandardItem(QString("Rate"));
        } else {
            item = new QStandardItem(QString(std::to_string(order.rating).c_str()));
        }
        model->setItem(i, 5, item);
    } else {
        item = new QStandardItem(QString("Cancel"));
        model->setItem(i, 5, item);
    }

    item = new QStandardItem(QString(std::to_string(order.id).c_str()));
    model->setItem(i, 6, item);

    if (order.status == db::Order::deleted){
        for (int j = 0; j < 5 + comments; ++j){
            model->setData(model->index(i, j), QColor(Qt::gray), Qt::BackgroundRole);
        }
    }
    ++i;
}

void ChoiceWindow::createTableView(QStandardItemModel* model, QStringList& horizontalHeader, QTableView* tableView, const int& size) {
    model->setHorizontalHeaderLabels(horizontalHeader);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ChoiceWindow::globalUpdate() {
    updateComboBox();
    updateTableViews();
}

void ChoiceWindow::updateComboBox() {
    try{
        ui->masterComboBox->clear();
        showMasters();

        ui->companyComboBox->clear();
        showCompanies();

        ui->orderComboBox->clear();
        showVacantOrders(-1, -1);
    }
    catch(...){
        errorProcessing();
    }
}

void ChoiceWindow::updateTableViews() {
    try{
        auto bookedOrders = db::ClientAPI::listOrdersOfClient(clientToken);

        rowF = 0, rowC = 0;

        for (size_t i = 0; i < bookedOrders.size(); ++i) {
            auto order = db::ClientAPI::getOrderById(clientToken, bookedOrders[i]);
            auto master = db::ClientAPI::getEmployeeById(order.employeeId);
            auto company = db::ClientAPI::getCompanyById(order.companyId);
            const time_t timeStart = order.timeStart, timeFinish = order.duration + order.timeStart;
            if (timeFinish > time(NULL)){
                addOrderToTableView(item, modelFutureOrders, rowF, order, company, master, timeStart, timeFinish);
            } else {
                addOrderToTableView(item, modelCompletedOrders, rowC, order, company, master, timeStart, timeFinish, true);
            }
        }

        horizontalHeader.append(QList<QString>({"Event", "Company", "Master", "Start", "Finish", "Status"}));
        createTableView(modelFutureOrders, horizontalHeader, ui->futureOrdersTableView, bookedOrders.size());
        ui->futureOrdersTableView->setColumnHidden(6, true);
        horizontalHeader.pop_back();
        horizontalHeader.append("My rate");
        createTableView(modelCompletedOrders, horizontalHeader, ui->completedOrdersTableView, bookedOrders.size());
        ui->completedOrdersTableView->setColumnHidden(6, true);

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
