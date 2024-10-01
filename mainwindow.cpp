#include <src/whole_task_list_window/ui_wholetasklistwindow.h>
#include <ui_mainwindow.h>
#include "mainwindow.h"
#include "src/edit_task_src/edittaskwindow.h"

MainWindow::MainWindow( QWidget *parent,TaskManager* const taskManagerPtr )
    :  QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,_taskManagerPtr(taskManagerPtr)
    ,_taskEditWindow(new editTaskWindow(taskManagerPtr,this))
    ,_sureToRemoveTaskWindow(new SureToRemoveTaskWindow(this))
    ,_sureToDeleteAllTaskWindow(new SureToDeleteAllTasks(this))
    ,_wholeTaskListWindow(new WholeTaskListWindow(taskManagerPtr,this))
{

    ui->setupUi(this);

    connect(_taskEditWindow,&editTaskWindow::on_Task_Edited,this,&MainWindow::completeTaskEdit);
    connect(ui->editTaskButton,&QPushButton::clicked,_taskEditWindow ,&editTaskWindow::Open);
    connect(_sureToRemoveTaskWindow,&SureToRemoveTaskWindow::accepted,this,&MainWindow::removeCurrentTask);
    connect(ui->removeTaskButton,&QPushButton::clicked,_sureToRemoveTaskWindow,&SureToRemoveTaskWindow::show);
    connect(_sureToDeleteAllTaskWindow,&SureToDeleteAllTasks::accepted,this,&MainWindow::deleteAllTasks);
    connect(ui->addTaskButton,&QPushButton::clicked,this,&MainWindow::addTask);
    connect(ui->calendarWidget,&QCalendarWidget::selectionChanged,this, &MainWindow::chooseDay);
    connect(ui->listWidget,&QListWidget::currentItemChanged,this,&MainWindow::chooseTask);

    _taskManagerPtr->ChooseDay(QDate::currentDate().toString());
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    _wholeTaskListWindow->hide();
    disableTaskDetailFrame();
}

MainWindow::~MainWindow()
{
    disconnect(_taskEditWindow,&editTaskWindow::on_Task_Edited,this,&MainWindow::completeTaskEdit);
    disconnect(ui->editTaskButton,&QPushButton::clicked,_taskEditWindow ,&editTaskWindow::Open);
    disconnect(_sureToRemoveTaskWindow,&SureToRemoveTaskWindow::accepted,this,&MainWindow::removeCurrentTask);
    disconnect(ui->removeTaskButton,&QPushButton::clicked,_sureToRemoveTaskWindow,&SureToRemoveTaskWindow::show);
    disconnect(_sureToDeleteAllTaskWindow,&SureToDeleteAllTasks::accepted,this,&MainWindow::deleteAllTasks);
    disconnect(ui->addTaskButton,&QPushButton::clicked,this,&MainWindow::addTask);
    disconnect(ui->calendarWidget,&QCalendarWidget::selectionChanged,this, &MainWindow::chooseDay);
    disconnect(ui->listWidget,&QListWidget::currentItemChanged,this,&MainWindow::chooseTask);

    delete _wholeTaskListWindow;
    delete _taskEditWindow;
    delete _sureToRemoveTaskWindow;
    delete _sureToDeleteAllTaskWindow;
    delete ui;
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

void MainWindow::addTask()
{
    _taskManagerPtr->Add();
    updateTaskList();
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

void MainWindow::completeTaskEdit()
{
    int currentRow = ui->listWidget->currentIndex().row();
    updateTaskList();
    ui->listWidget->setCurrentRow(currentRow);
}

void MainWindow::updateTaskDetailFrame()
{
    const SingleTask& task = _taskManagerPtr->ChoosedTask();
    ui->label_5->setText(task.Name());
    ui->label_4->setText(task.Definition());
    ui->timeEdit->setTime(task.StartTime());
    ui->timeEdit_2->setTime(task.EndTime());
    ui->label_8->setText(_taskManagerPtr->ChoosedDay());
}

void MainWindow::removeCurrentTask()
{
    _taskManagerPtr->Remove();
    updateTaskList();
}

void MainWindow::deleteAllTasks()
{
    _taskManagerPtr->RemoveAll();
}

void MainWindow::chooseDay()
{
    _taskManagerPtr->ChooseDay(ui->calendarWidget->selectedDate().toString());
    updateChooedDayText();
    updateTaskList( );
}

void MainWindow::chooseTask(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current)
    {
        _taskManagerPtr->ChooseTask(current->text());
        updateTaskDetailFrame();
        enableTaskDetailFrame();
    }
    else
    {
        disableTaskDetailFrame();
    }
}

/////////////////////////
// Actions

void MainWindow::on_actionShow_All_Tasks_triggered()
{
    _wholeTaskListWindow->UpdateDays();
    _wholeTaskListWindow->show();
}

void MainWindow::on_actionDelete_All_Tasks_triggered()
{
    _sureToDeleteAllTaskWindow->show();
}

// Actions
/////////////////////////






