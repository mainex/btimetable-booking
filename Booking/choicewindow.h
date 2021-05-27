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
    explicit ChoiceWindow(const long long, QWidget *parent = nullptr);
    ~ChoiceWindow();
    const long long clientId;
    int rowF = 0, rowC = 0;
    QStandardItem *item;
    QStandardItemModel *modelFutureOrders, *modelCompletedOrders;
    QStringList horizontalHeader;
    void updateComboBox();
    void updateTableViews();
    void globalUpdate();
    void showVacantOrders(long long companyId, long long employeeId, long long leastTimeStart = 0, long long leastDuration = 0, db::sortParam sortBy = db::byId, bool reversed = true);
    void showMasters();
    void showCompanies();
    static void addOrderToTableView(QStandardItem*, QStandardItemModel*, int&, db::Order&, db::Company&, db::Employee&, const time_t&, const time_t&, bool);
    static void createTableView(QStandardItemModel*, QStringList&, QTableView*, const int&);
    std::string to_string(db::Order&, db::Employee&, db::Company&);
    void errorProcessing();

private:
    Ui::ChoiceWindow *ui;
};

#endif // CHOICEWINDOW_H
