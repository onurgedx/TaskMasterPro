#include "TaskStoreManager.h"

TaskStoreManager::TaskStoreManager(TaskManager* const taskManager) :_taskManager(taskManager)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");

    _db.setDatabaseName("tasks.db");

    if (!_db.open()) {
        qDebug() << "Database is not opened!";
        qDebug() << _db.lastError().text();
    }
    else {
        qDebug() << "Database is opened!";
    }

    ReadData();
}

TaskStoreManager::~TaskStoreManager()
{
    WriteData();
    RemoveData();
    if(_db.isOpen())
    {
        _db.close();
    }
}

void  TaskStoreManager::ReadData() const
{
    QSqlQuery query;
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS tasks ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "day TEXT NOT NULL, "
                               "description TEXT NOT NULL);";

    if (!query.exec(createTableQuery)) {
        qDebug() << "table could not be created:";
        qDebug() << query.lastError().text();
    } else {
        qDebug() << "Table is created";
    }


    if (!query.exec("SELECT id, day, description FROM tasks")) {
        qDebug() << "Veriler okunamadi";
        qDebug() << query.lastError().text();
        return;
    }

    while(query.next())
    {
        int id = query.value(0).toInt();
        QString day = query.value(1).toString();
        QString description = query.value(2).toString();
        _taskManager->Add(day,SingleTask(description,id));
    }
}

void TaskStoreManager::WriteData() const
{
    QSqlQuery query;

    for (auto iter = _taskManager->_taskMapPtr->begin(); iter != _taskManager->_taskMapPtr->end(); iter++)
    {
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
        {

            if(iter2->IsNew())// Add
            {
                query.prepare("INSERT INTO tasks ( day, description) VALUES ( :day, :description)");
                query.bindValue(":day", iter->first);
                query.bindValue(":description", iter2->SQLRecord());
                if (!query.exec()) {
                qDebug() << "Adding data is failed: " << query.lastError().text();
                }
                else
                {
                    qDebug() << "Data added "   ;
                }
            }
            else if(iter2->IsEdit())
            {
                query.prepare("UPDATE tasks SET description = :description WHERE id = :id");
                query.bindValue(":id", iter2->ID());
                query.bindValue(":description",iter2->SQLRecord());

                query.exec();
                if (!query.exec()) {
                    qDebug() << "Update data is failed: " << query.lastError().text();
                }
                else
                {
                    qDebug() << "Data Updated "   ;
                }
            }
        }
    }
}

void TaskStoreManager::RemoveData() const
{
    QSqlQuery query;
     /*if (!query.exec("DELETE FROM tasks")) {}*/

    for (auto iter = _taskManager->_removedTaskMapPtr->begin(); iter != _taskManager->_removedTaskMapPtr->end(); iter++)
    {
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
        {

            query.prepare("DELETE FROM tasks WHERE id = :id");
            query.bindValue(":id",iter2->ID());
            if(!query.exec())
            {
                qDebug()<<"Removing data is failed!"<<iter2->ID() <<query.lastError().text();
            }
            else
            {
                qDebug()<< "Data Deleted";
            }

        }}
}

void TaskStoreManager::DeleteAllData() const
{
    QSqlQuery query;
    if (!query.exec("DELETE FROM tasks"))
    {
        qDebug()<< "Deleting all data is failed!";
    }
}
