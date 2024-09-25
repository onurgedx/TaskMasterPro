#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <qdatetime.h>
#include "../task/Task.h"

#define SingleTaskList std::vector<SingleTask>
#define TaskMap std::unordered_map<QString,SingleTaskList>

class TaskStoreManager;

class TaskManager
{
private:
    int _taskCount=0;
    TaskMap* _taskMapPtr ;
    TaskMap* _removedTaskMapPtr;
    SingleTask* _choosedTaskPtr;
    QString _choosedDay;
    friend TaskStoreManager;
public :
    TaskManager();
    ~TaskManager();

    SingleTask& Get(const QString& day,int index) const;

    void Add(QString& day,SingleTask&& task );
    void Add();
    void Remove();
    void RemoveAll();
    void Edit(QTime startTime , QTime endTime, QString name, QString definition);
    void ChooseTask(int index);
    void ChooseTask(const QString& name);
    void ChooseDay(const QString& day);

    const std::pair<TaskMap::iterator, TaskMap::iterator> GetIters()const ;

    const SingleTaskList& TasksAt(const QString& day)const;
    const SingleTaskList&  ChoosedDayTasks();
    const SingleTask& ChoosedTask() const;
    const QString& ChoosedDay() const;



};



#endif // TASKMANAGER_H
