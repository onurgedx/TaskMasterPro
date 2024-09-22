#ifndef EDITTASKWINDOW_H
#define EDITTASKWINDOW_H

#include <QDialog>
#include "../task_manager/TaskManager.h"
namespace Ui {
class editTaskWindow;
}

class editTaskWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editTaskWindow(TaskManager* taskManagerPtr, QWidget *parent = nullptr);
    ~editTaskWindow();
    void Update();

public: signals:
    void on_Task_Edited();

private slots:
    void on_buttonBox_accepted();

    void on_lineEdit_textChanged(const QString &arg1);

private:

    Ui::editTaskWindow *ui;
    TaskManager* const _taskManagerPtr;
};



#endif // EDITTASKWINDOW_H
