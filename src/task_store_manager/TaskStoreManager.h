#ifndef TASKSTOREMANAGER_H
#define TASKSTOREMANAGER_H

#include "../task_manager/TaskManager.h"
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>


class TaskStoreManager
{
private:
    QSqlDatabase _db;
    TaskManager* const _taskManager;
public:

    TaskStoreManager(TaskManager* const taskManager );
    ~TaskStoreManager();

    void ReadData() const;
    void WriteData() const;
    void RemoveData() const;
    void DeleteAllData() const;

};


#endif // TASKSTOREMANAGER_H
