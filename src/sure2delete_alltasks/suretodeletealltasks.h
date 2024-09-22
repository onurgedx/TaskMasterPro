#ifndef SURETODELETEALLTASKS_H
#define SURETODELETEALLTASKS_H

#include <QDialog>

namespace Ui {
class SureToDeleteAllTasks;
}

class SureToDeleteAllTasks : public QDialog
{
    Q_OBJECT

public:
    explicit SureToDeleteAllTasks(QWidget *parent = nullptr);
    ~SureToDeleteAllTasks();

private:
    Ui::SureToDeleteAllTasks *ui;
};

#endif // SURETODELETEALLTASKS_H
