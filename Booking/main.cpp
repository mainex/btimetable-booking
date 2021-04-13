#include "mainwindow.h"

#include <QApplication>
#include "entities.h"
#include "testdatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
