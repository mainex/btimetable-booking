#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include <QMainWindow>

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
private:
    Ui::ChoiceWindow *ui;
};

#endif // CHOICEWINDOW_H
