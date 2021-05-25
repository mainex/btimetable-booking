#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QTableView>
#include "ClientAPI.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ChoiceWindow;
}
QT_END_NAMESPACE

class ChoiceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChoiceWindow(const int, QWidget *parent = nullptr);
    ~ChoiceWindow();
    unsigned long long clientId;
    void update();
    void showVacantOrders();
    static void addOrderToTableView(QStandardItem*, QStandardItemModel*, size_t&, db::Order&, db::Company&, db::Employee&, const time_t&, const time_t&, bool);
    static void createTableView(QStandardItemModel*, QStringList&, QTableView*, const size_t&);
    std::string to_string(db::Order&, db::Employee&, db::Company&);
private:
    Ui::ChoiceWindow *ui;
};

#endif // CHOICEWINDOW_H
