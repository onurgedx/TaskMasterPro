#ifndef WHOLETASKLISTWINDOW_H
#define WHOLETASKLISTWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include "../task_manager/TaskManager.h"


namespace Ui {
class WholeTaskListWindow;
}

class WholeTaskListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WholeTaskListWindow(TaskManager const * const taskManagerPtr , QWidget *parent = nullptr);
    ~WholeTaskListWindow();

    void UpdateDays();
    void UpdateTasks( );

private slots:
    void on_dayListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::WholeTaskListWindow *ui;    
    TaskManager const * const  _taskManagerPtr;
};

#endif // WHOLETASKLISTWINDOW_H
