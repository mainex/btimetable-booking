#ifndef ERRORPROCESSING_H
#define ERRORPROCESSING_H
#include "ClientAPI.h"
#include <QWidget>

class ErrorProcessing
{
public:
    ErrorProcessing();

    void bttFatalError(db::bttFatalError, QWidget*);
    static void bttError(db::bttError, QWidget*);
};

#endif // ERRORPROCESSING_H
