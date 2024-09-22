#include "TaskManager.h"

TaskManager::TaskManager(): _taskMapPtr(new TaskMap),_removedTaskMapPtr(new TaskMap)
{
}

TaskManager::~TaskManager()
{
    delete _taskMapPtr;
    delete _removedTaskMapPtr;
}

void TaskManager::Add(QString& day,SingleTask&& task )
{
    ++_taskCount;
    (*_taskMapPtr)[day].push_back(std::move(task));
}

void TaskManager::Add()
{
    ++_taskCount;
    int taskIndex = _taskCount;
    bool add=true;
    for(auto iter = (*_taskMapPtr)[_choosedDay].begin();iter!= (*_taskMapPtr)[_choosedDay].end();iter++)
    {
        if(iter->Name() == NEW_TASK_NAME)
        {
            add = false;
            Add();
            break;
        }
    }
    if(add)
    {
        (*_taskMapPtr)[_choosedDay].push_back(SingleTask(_taskCount));
    }
}

void TaskManager::Edit(QTime startTime , QTime endTime, QString name, QString definition)
{
    _choosedTaskPtr->Edit(startTime,endTime,name,definition);
}

void TaskManager::Remove( )
{
    auto iter = (*_taskMapPtr)[_choosedDay].begin() ;
    for(; iter!=(*_taskMapPtr)[_choosedDay].end() ;iter++ )
    {
        if (*iter == *_choosedTaskPtr)
        {
            break;
        }
    }
    if(!_choosedTaskPtr->IsNew())
    {
        (*_removedTaskMapPtr)[_choosedDay].push_back(std::move(*_choosedTaskPtr));
    }
    (*_taskMapPtr)[_choosedDay].erase(iter);
}

void TaskManager::RemoveAll()
{

    for(auto iter1 = _taskMapPtr->begin();iter1!= _taskMapPtr->end();iter1++ )
    {

        for(auto iter2 = iter1->second.begin();iter2 != iter1->second.end();iter2++)
        {
            if(!_choosedTaskPtr->IsNew())
            {
                (*_removedTaskMapPtr)[_choosedDay].push_back(std::move(*iter2));
            }
        }
    }
    _taskMapPtr->clear();
}

void TaskManager::ChooseTask(int index)
{
    _choosedTaskPtr = &(*_taskMapPtr)[_choosedDay][index];
}

void TaskManager::ChooseTask(const QString& name)
{
    SingleTaskList& tasks= (*_taskMapPtr)[_choosedDay];
    for(auto taskIter =tasks.begin();taskIter != tasks.end();taskIter++)
    {
        if(name == taskIter->Name())
        {
            _choosedTaskPtr = &(*taskIter);
        }
    }
}

void TaskManager::ChooseDay(const QString& day)
{
    _choosedDay = day;
}

SingleTask& TaskManager::Get(const QString& day,int index) const
{
    return (*_taskMapPtr)[day][index];
}

const SingleTaskList&  TaskManager::ChoosedDayTasks()
{
    return (*_taskMapPtr)[_choosedDay];
}

const SingleTask& TaskManager::ChoosedTask() const
{
    return *_choosedTaskPtr;
}

const QString& TaskManager::ChoosedDay() const
{
    return _choosedDay;
}
