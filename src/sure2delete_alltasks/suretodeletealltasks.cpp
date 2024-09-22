#include "suretodeletealltasks.h"
#include "ui_suretodeletealltasks.h"

SureToDeleteAllTasks::SureToDeleteAllTasks(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SureToDeleteAllTasks)
{
    ui->setupUi(this);
}

SureToDeleteAllTasks::~SureToDeleteAllTasks()
{
    delete ui;
}
