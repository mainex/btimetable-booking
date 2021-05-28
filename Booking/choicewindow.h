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
    explicit ChoiceWindow(const std::string, QWidget *parent = nullptr);
    ~ChoiceWindow();
    std::string clientToken;
    int rowF = 0, rowC = 0;
    QStandardItem *item;
    QStandardItemModel *modelFutureOrders, *modelCompletedOrders;
    QStringList horizontalHeader;
    void updateComboBox();
    void updateTableViews();
    void globalUpdate();
    void showVacantOrders(long long companyId, long long employeeId, db::sortParam sorted = db::sortParam::byTimeStart,long long minTimeStart = 0,long long maxTimeStart = -1, long long minDuration = 0, long long maxDuration = -1);
    void showMasters();
    void showCompanies();
    static void addOrderToTableView(QStandardItem*, QStandardItemModel*, int&, db::Order&, db::Company&, db::Employee&, const time_t&, const time_t&, bool);
    static void createTableView(QStandardItemModel*, QStringList&, QTableView*, const int&);
    std::string to_string(db::Order&, db::Employee&, db::Company&);

private:
    Ui::ChoiceWindow *ui;
};

#endif // CHOICEWINDOW_H
