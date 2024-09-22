#include "suretoremovetaskwindow.h"
#include "ui_suretoremovetaskwindow.h"

SureToRemoveTaskWindow::SureToRemoveTaskWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SureToRemoveTaskWindow)
{
    ui->setupUi(this);
}

SureToRemoveTaskWindow::~SureToRemoveTaskWindow()
{
    delete ui;
}
