#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choicewindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    try{
        ui->setupUi(this);
        auto l = db::ClientAPI::listCompanies();
        for (auto h : l) {
            auto r = db::ClientAPI::listEmployeesOfCompany(h);
            for (auto y : r) {
                auto d = db::ClientAPI::listOrders(h, y, db::Order::booked);
                for (auto s : d)
                    db::ClientAPI::cancelOrder(s);
            }
        }
        ui->enterPasswordLineEdit->setEchoMode(QLineEdit::Password);
        ui->enterPasswordAgainLineEdit->setEchoMode(QLineEdit::Password);
        ui->enterPasswordForAuthorizationLineEdit->setEchoMode(QLineEdit::Password);
        ui->isEmailOkLabel->setFixedWidth(60);
        ui->isNameOkLabel->setFixedWidth(60);
        ui->isPasswordOkLabel->setFixedWidth(60);
        ui->isTelephoneOkLabel->setFixedWidth(60);
        ui->isPasswordAgainOkLabel->setFixedWidth(60);
        const QRegularExpression telephoneRegExpr("\\+7(-\\d{3}){2}(-\\d{2}){2}");
        ui->enterTelephoneLineEdit->setValidator(new QRegularExpressionValidator(telephoneRegExpr));
        ui->enterTelephoneForAuthorizationLineEdit->setValidator(new QRegularExpressionValidator(telephoneRegExpr));
        connect(ui->pushButton, &QPushButton::clicked, [this]{
            email = ui->enterEmailLineEdit->text().toUtf8().constData();
            telephone = ui->enterTelephoneLineEdit->text().toUtf8().constData();
            name = ui->enterNameLineEdit->text().toUtf8().constData();
            std::hash<std::string> h;
            const size_t hashedPassword = h(ui->enterPasswordLineEdit->text().toUtf8().constData());
            const size_t hashedPasswordAgain = h(ui->enterPasswordAgainLineEdit->text().toUtf8().constData());
            const size_t hashedNull = h("");
            if(telephone.size()) {
                ui->isTelephoneOkLabel->setText("Good");
            } else {
                ui->isTelephoneOkLabel->setText("Bad");
            }
            if(email.size()) {
                ui->isEmailOkLabel->setText("Good");
            } else {
                ui->isEmailOkLabel->setText("Bad");
            }
            if(name.size()) {
                ui->isNameOkLabel->setText("Good");
            } else {
                ui->isNameOkLabel->setText("Bad");
            }
            if(hashedNull != hashedPassword && hashedPassword == hashedPasswordAgain) {
                ui->isPasswordOkLabel->setText("Good");
                ui->isPasswordAgainOkLabel->setText("Good");
                password = std::to_string(hashedPassword);
            } else {
                ui->isPasswordOkLabel->setText("Bad");
                ui->isPasswordAgainOkLabel->setText("Bad");
            }
            if (ui->isEmailOkLabel->text().toStdString() == "Good" &&
                    ui->isTelephoneOkLabel->text().toStdString() == "Good" &&
                    ui->isNameOkLabel->text().toStdString() == "Good" &&
                    ui->isPasswordOkLabel->text().toStdString() == "Good") {
                const long long idB = db::ClientAPI::createClient(telephone, password, name, email);
                ChoiceWindow *w = new ChoiceWindow(idB, nullptr);
                close();
                w->show();
            } else {
                ui->label->setText("Check information, please, registration did not complete.");
            }
        });

        connect(ui->enterButton, &QPushButton::clicked, [this] {
            std::hash<std::string> h;
            const size_t hashedPassword = h(ui->enterPasswordForAuthorizationLineEdit->text().toUtf8().constData());
            std::string password1 = std::to_string(hashedPassword);
            std::string telephone1 = ui->enterTelephoneForAuthorizationLineEdit->text().toUtf8().constData();
            const long long idA = db::ClientAPI::authorizeClient(telephone1, password1);
            ChoiceWindow *w = new ChoiceWindow(idA, nullptr);
            close();
            w->show();
        });

        connect(ui->actionExit, &QAction::triggered, [this](){
            close();
        });
    }
    catch(...){
        QMessageBox::information(this, QString("Error!"), QString("Error"));
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
