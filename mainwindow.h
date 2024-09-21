#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "edittaskwindow.h"
#include "suretodeletealltasks.h"
#include "suretoremovetaskwindow.h"
#include <QMainWindow>
#include <qlistwidget.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr ,TaskManager* const taskManagerPtr =nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();
    void on_calendarWidget_selectionChanged();
    void on_pushButton_3_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_pushButton_9_clicked();
    void on_actionDelete_All_Tasks_triggered();

private:
    Ui::MainWindow *ui;
    TaskManager* const _taskManagerPtr;
    editTaskWindow* _taskWindow;
    SureToRemoveTaskWindow* _sureToRemoveTaskWindow;
    SureToDeleteAllTasks* _sureToDeleteAllTaskWindow;
    void updateTaskList();
    void disableTaskDetailFrame();
    void enableTaskDetailFrame();
    void completeTaskEdit();
    void updateListWidget();
    void removeCurrentTask();
    void updateChooedDayText();
    void deleteAllTasks();

};
#endif // MAINWINDOW_H
