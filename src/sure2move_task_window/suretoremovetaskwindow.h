#ifndef SURETOREMOVETASKWINDOW_H
#define SURETOREMOVETASKWINDOW_H

#include <QDialog>

namespace Ui {
class SureToRemoveTaskWindow;
}

class SureToRemoveTaskWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SureToRemoveTaskWindow(QWidget *parent = nullptr);
    ~SureToRemoveTaskWindow();

private:
    Ui::SureToRemoveTaskWindow *ui;
};

#endif // SURETOREMOVETASKWINDOW_H
