#include "wholetasklistwindow.h"
#include <src/whole_task_list_window/ui_wholetasklistwindow.h>

WholeTaskListWindow::WholeTaskListWindow(TaskManager const * const taskManagerPtr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WholeTaskListWindow)
    , _taskManagerPtr(taskManagerPtr)
{
    ui->setupUi(this);
}

WholeTaskListWindow::~WholeTaskListWindow()
{
    delete ui;
}

void WholeTaskListWindow::UpdateDays()
{
    ui->dayListWidget->clear();
    auto beginendpair = _taskManagerPtr->GetIters();
    for(auto iter = beginendpair.first;iter != beginendpair.second;++iter)
    {
        if(!iter->second.empty())
        {
            ui->dayListWidget->addItem((*iter).first);
        }
    }
}

void WholeTaskListWindow::on_dayListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->taskListWidget->clear();
    if(current)
    {
        for(auto &task : _taskManagerPtr->TasksAt(current->text()))
        {
            ui->taskListWidget->addItem(task.Name());
        }
    }
}

void  WholeTaskListWindow::UpdateTasks( )
{
    ui->taskListWidget->clear();
    QString day = ui->dayListWidget->currentItem()->text();
    for(auto &task : _taskManagerPtr->TasksAt(day ))
    {
        ui->taskListWidget->addItem(task.Name());
    }
}
