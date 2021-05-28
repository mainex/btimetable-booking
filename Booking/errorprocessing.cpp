#include "errorprocessing.h"
#include <QMessageBox>
#include<QString>

ErrorProcessing::ErrorProcessing()
{

}

void ErrorProcessing::bttError(db::bttError err, QWidget* parent) {
    QMessageBox::information(parent, QString("Error!"), QString(err.what()));
}

void ErrorProcessing::bttFatalError(db::bttFatalError err, QWidget* parent){

}
