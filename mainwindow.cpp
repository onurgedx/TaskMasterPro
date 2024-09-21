#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "edittaskwindow.h"

MainWindow::MainWindow( QWidget *parent,TaskManager* const taskManagerPtr )
    :  QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,_taskManagerPtr(taskManagerPtr)
    ,_taskWindow(new editTaskWindow(taskManagerPtr,this))
    ,_sureToRemoveTaskWindow(new SureToRemoveTaskWindow(this))
    ,_sureToDeleteAllTaskWindow( new SureToDeleteAllTasks(this))
{
    ui->setupUi(this);
    disableTaskDetailFrame();
    connect(_taskWindow,&editTaskWindow::on_Task_Edited,this,&MainWindow::completeTaskEdit);
    connect(_sureToRemoveTaskWindow,&SureToRemoveTaskWindow::accepted,this,&MainWindow::removeCurrentTask);
    connect(_sureToDeleteAllTaskWindow,&SureToDeleteAllTasks::accepted,this,&MainWindow::deleteAllTasks);
    _taskManagerPtr->ChooseDay(QDate::currentDate().toString());
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    disconnect(_taskWindow,&editTaskWindow::on_Task_Edited,this,&MainWindow::completeTaskEdit);
    disconnect(_sureToRemoveTaskWindow,&SureToRemoveTaskWindow::accepted,this,&MainWindow::removeCurrentTask);
    disconnect(_sureToDeleteAllTaskWindow,&SureToDeleteAllTasks::accepted,this,&MainWindow::deleteAllTasks);
    delete _taskWindow;
    delete _sureToRemoveTaskWindow;
    delete _sureToDeleteAllTaskWindow;
    delete ui;
}

void MainWindow::on_pushButton_5_clicked()
{
    _taskManagerPtr->Add();
    updateTaskList();
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    _taskManagerPtr->ChooseDay(ui->calendarWidget->selectedDate().toString());
    updateChooedDayText();
    updateTaskList( );
}

void MainWindow::updateChooedDayText()
{
    ui->label_7->setText(_taskManagerPtr->ChoosedDay());

}

void MainWindow::updateTaskList()
{
    ui->listWidget->clear();
    const SingleTaskList&  tasks = _taskManagerPtr->ChoosedDayTasks();
    if(!tasks.empty() )
    {
        for(auto iter = tasks.begin();iter !=tasks.end();iter++)
        {
            ui->listWidget->addItem(iter->Name());
        }
    }
}

// task edit Window opening
void MainWindow::on_pushButton_3_clicked()
{
    _taskWindow->setModal(true);
    _taskWindow->Update();
    _taskWindow->show();
}

void MainWindow::disableTaskDetailFrame()
{
    ui->frame->setEnabled(false);
    ui->frame->hide();
}

void MainWindow::enableTaskDetailFrame()
{
    ui->frame->setEnabled(true);
    ui->frame->show();
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current)
    {
        _taskManagerPtr->ChooseTask(current->text());
        updateListWidget();
        enableTaskDetailFrame();
    }
    else
    {
        disableTaskDetailFrame();
    }
}

void MainWindow::completeTaskEdit()
{
    int currentRow = ui->listWidget->currentIndex().row();
    updateTaskList();
    ui->listWidget->setCurrentRow(currentRow);
}

void MainWindow::updateListWidget()
{
    const SingleTask& task = _taskManagerPtr->ChoosedTask();
    ui->label_5->setText(task.Name());
    ui->label_4->setText(task.Definition());
    ui->timeEdit->setTime(task.StartTime());
    ui->timeEdit_2->setTime(task.EndTime());
    ui->label_8->setText(_taskManagerPtr->ChoosedDay());
}

void MainWindow::on_pushButton_9_clicked()
{
    _sureToRemoveTaskWindow->show();
}

void MainWindow::removeCurrentTask()
{
    _taskManagerPtr->Remove();
    updateTaskList();
}

void MainWindow::on_actionDelete_All_Tasks_triggered()
{
    _sureToDeleteAllTaskWindow->show();
}

void MainWindow::deleteAllTasks()
{
    _taskManagerPtr->RemoveAll();
}
