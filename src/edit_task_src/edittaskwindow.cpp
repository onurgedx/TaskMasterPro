#include "edittaskwindow.h"
#include "ui_edittaskwindow.h"
editTaskWindow::editTaskWindow(TaskManager* const taskManagerPtr , QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::editTaskWindow)
    ,_taskManagerPtr(taskManagerPtr)
{
    ui->setupUi(this);
    ui->inappropriate->hide();
    this->setModal(true);
}

editTaskWindow::~editTaskWindow()
{
    delete ui;
}

// Updates initial values of edit task inputs
void editTaskWindow::Open()
{
    const SingleTask& choosedTask = _taskManagerPtr->ChoosedTask();
    ui->lineEdit->setText(choosedTask.Name());
    ui->lineEdit_2->setText(choosedTask.Definition());
    ui->timeEdit->setTime(choosedTask.StartTime());
    ui->timeEdit_2->setTime(choosedTask.EndTime());
    show();
}

//Updates choosed task
void editTaskWindow::on_buttonBox_accepted()
{
    _taskManagerPtr->Edit(ui->timeEdit->time(),ui->timeEdit_2->time(),ui->lineEdit->displayText(),ui->lineEdit_2->displayText());
    emit on_Task_Edited();
}

// Checks whether ChoosedDayTasks has a SingleTask which name is <arg1>
void editTaskWindow::on_lineEdit_textChanged(const QString &arg1)
{
    const SingleTaskList& taskList =_taskManagerPtr->ChoosedDayTasks();
    const SingleTask& choosedTask = _taskManagerPtr->ChoosedTask();
    for(auto iter =taskList.begin(); iter != taskList.end();iter++)
    {
        if( &choosedTask == &(*iter))
        {
            continue;
        }

        if(arg1 == iter->Name())
        {
            ui->buttonBox->buttons()[0]->setDisabled(true);
            ui->inappropriate->show();
            return;
        }
    }
    ui->inappropriate->hide();
    ui->buttonBox->buttons()[0]->setEnabled(true);
}

