#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/task_manager/TaskManager.h"
#include "src/edit_task_src/edittaskwindow.h"
#include "src/sure2move_task_window/suretoremovetaskwindow.h"
#include "src/task_manager/TaskManager.h"
#include "src/sure2delete_alltasks/suretodeletealltasks.h"
#include "src/sure2move_task_window/suretoremovetaskwindow.h"
#include "src/whole_task_list_window/wholetasklistwindow.h"
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
    void on_actionDelete_All_Tasks_triggered();
    void on_actionShow_All_Tasks_triggered();

private:
    Ui::MainWindow *ui;
    TaskManager* const _taskManagerPtr;
    editTaskWindow* const _taskEditWindow;
    SureToRemoveTaskWindow* const _sureToRemoveTaskWindow;
    SureToDeleteAllTasks* const _sureToDeleteAllTaskWindow;
    WholeTaskListWindow* const _wholeTaskListWindow;
    void updateTaskList();
    void disableTaskDetailFrame();
    void enableTaskDetailFrame();
    void completeTaskEdit();
    void updateTaskDetailFrame();
    void removeCurrentTask();
    void updateChooedDayText();
    void deleteAllTasks();
    void addTask();
    void chooseDay();
    void chooseTask(QListWidgetItem *current, QListWidgetItem *previous);
};
#endif // MAINWINDOW_H
