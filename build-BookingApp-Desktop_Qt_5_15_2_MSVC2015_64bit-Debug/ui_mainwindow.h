/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QFormLayout *formLayout_3;
    QLabel *enterIdLabel;
    QLineEdit *enterIdLineEdit;
    QLabel *enterEmailLabel;
    QLineEdit *enterEmailLineEdit;
    QLabel *enterTelephoneLabel;
    QLineEdit *enterTelephoneLineEdit;
    QPushButton *pushButton;
    QFormLayout *formLayout_4;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *idLabel;
    QLabel *isIdOkLabel;
    QHBoxLayout *horizontalLayout_5;
    QLabel *emailLabel;
    QLabel *isEmailOkLabel;
    QHBoxLayout *horizontalLayout_6;
    QLabel *telephoneLabel;
    QLabel *isTelephoneOkLabel;
    QLabel *label;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(746, 408);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout_2->addWidget(tableView);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        enterIdLabel = new QLabel(centralwidget);
        enterIdLabel->setObjectName(QString::fromUtf8("enterIdLabel"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, enterIdLabel);

        enterIdLineEdit = new QLineEdit(centralwidget);
        enterIdLineEdit->setObjectName(QString::fromUtf8("enterIdLineEdit"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, enterIdLineEdit);

        enterEmailLabel = new QLabel(centralwidget);
        enterEmailLabel->setObjectName(QString::fromUtf8("enterEmailLabel"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, enterEmailLabel);

        enterEmailLineEdit = new QLineEdit(centralwidget);
        enterEmailLineEdit->setObjectName(QString::fromUtf8("enterEmailLineEdit"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, enterEmailLineEdit);

        enterTelephoneLabel = new QLabel(centralwidget);
        enterTelephoneLabel->setObjectName(QString::fromUtf8("enterTelephoneLabel"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, enterTelephoneLabel);

        enterTelephoneLineEdit = new QLineEdit(centralwidget);
        enterTelephoneLineEdit->setObjectName(QString::fromUtf8("enterTelephoneLineEdit"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, enterTelephoneLineEdit);


        verticalLayout_2->addLayout(formLayout_3);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        idLabel = new QLabel(centralwidget);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        horizontalLayout_4->addWidget(idLabel);

        isIdOkLabel = new QLabel(centralwidget);
        isIdOkLabel->setObjectName(QString::fromUtf8("isIdOkLabel"));

        horizontalLayout_4->addWidget(isIdOkLabel);


        formLayout_4->setLayout(0, QFormLayout::FieldRole, horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        emailLabel = new QLabel(centralwidget);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));

        horizontalLayout_5->addWidget(emailLabel);

        isEmailOkLabel = new QLabel(centralwidget);
        isEmailOkLabel->setObjectName(QString::fromUtf8("isEmailOkLabel"));

        horizontalLayout_5->addWidget(isEmailOkLabel);


        formLayout_4->setLayout(1, QFormLayout::FieldRole, horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        telephoneLabel = new QLabel(centralwidget);
        telephoneLabel->setObjectName(QString::fromUtf8("telephoneLabel"));

        horizontalLayout_6->addWidget(telephoneLabel);

        isTelephoneOkLabel = new QLabel(centralwidget);
        isTelephoneOkLabel->setObjectName(QString::fromUtf8("isTelephoneOkLabel"));

        horizontalLayout_6->addWidget(isTelephoneOkLabel);


        formLayout_4->setLayout(2, QFormLayout::FieldRole, horizontalLayout_6);


        verticalLayout_2->addLayout(formLayout_4);


        verticalLayout->addLayout(verticalLayout_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 746, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        enterIdLabel->setText(QCoreApplication::translate("MainWindow", "ID \321\201\320\276\320\261\321\213\321\202\320\270\321\217:", nullptr));
        enterIdLineEdit->setText(QString());
        enterEmailLabel->setText(QCoreApplication::translate("MainWindow", "E-mail \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 example@domain.com:", nullptr));
        enterEmailLineEdit->setText(QString());
        enterTelephoneLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275 \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 +7-XXX-XXX-XX-XX:", nullptr));
        enterTelephoneLineEdit->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\261\321\200\320\276\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "E-mail:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275:", nullptr));
        idLabel->setText(QString());
        isIdOkLabel->setText(QCoreApplication::translate("MainWindow", "Bad", nullptr));
        emailLabel->setText(QString());
        isEmailOkLabel->setText(QCoreApplication::translate("MainWindow", "Bad", nullptr));
        telephoneLabel->setText(QString());
        isTelephoneOkLabel->setText(QCoreApplication::translate("MainWindow", "Bad", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\321\214\321\202\320\265 \320\264\320\260\320\275\320\275\321\213\320\265, \320\261\321\200\320\276\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\275\320\265 \320\267\320\260\320\262\320\265\321\200\321\210\320\265\320\275\320\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
