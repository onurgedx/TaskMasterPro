#include "Task.h"
#include <qdatetime.h>
SingleTask::SingleTask(int taskIndex): _startTime( QTime::currentTime() ), _endTime(QTime::currentTime()),_name(NEW_TASK_NAME),_definition("default definition"), _id(-1*taskIndex),_isNew(true),_isEdit(false)
{

}

SingleTask::SingleTask(SingleTask&& rr) noexcept
{
    this->_id = std::move(rr._id);
    this->_startTime = std::move(rr._startTime);
    this->_endTime =  std::move(rr._endTime);
    this->_name = std::move(rr._name);
    this->_definition = std::move(rr._definition);
    this->_isNew = std::move(rr._isNew);
    this->_isEdit = std::move(rr._isEdit);
}

SingleTask::SingleTask(const SingleTask& r)
{
    _id = r._id;
    _startTime = r.StartTime();
    _endTime = r.EndTime();
    _name = r.Name();
    _definition = r.Definition();
    _isNew =r.IsNew();
    _isEdit = r.IsEdit();
}

SingleTask::SingleTask(QString sqlDefinition,int id)
{
    _isEdit = false;
    _isNew = false;
    _id =id;
    QStringList listOfInitialize = sqlDefinition.split(SQL_SPLIT_TOOL);
    _startTime = QTime::fromString(listOfInitialize[0]);
    _endTime = QTime::fromString(listOfInitialize[1]);
    _name = listOfInitialize[2];
    _definition = listOfInitialize[3];
}

SingleTask::~SingleTask()
{

}

void SingleTask::Edit(QTime startTime , QTime endTime, QString name, QString definition)
{
    _isEdit=true;
    _startTime = startTime;
    _endTime = endTime;
    _name = name;
    _definition = definition;
}

QTime SingleTask::StartTime() const
{
    return _startTime;
}

QTime SingleTask::EndTime() const
{
    return _endTime;
}

QString SingleTask::Name() const
{
    return _name;
}

QString SingleTask::Definition() const
{
    return _definition;
}

int SingleTask::ID() const
{
    return _id;
}

bool SingleTask::IsNew() const
{
    return _isNew;
}

bool SingleTask::IsEdit() const
{
    return _isEdit;
}

QString SingleTask::SQLRecord() const
{
    return _startTime.toString() + SQL_SPLIT_TOOL +_endTime.toString() + SQL_SPLIT_TOOL + _name +SQL_SPLIT_TOOL+_definition;
}

SingleTask& SingleTask::operator=(const SingleTask& r)
{
    _startTime = r.StartTime();
    _endTime = r.EndTime();
    _name = r.Name();
    _definition = r.Definition();
    return *this;
}

bool SingleTask::operator==(const SingleTask& r) const
{
    return r.Name()==Name() && r.Definition() == Definition() && r.StartTime()== StartTime() && r.EndTime() == EndTime() && r.ID()== ID();
}

bool SingleTask::operator!=(const SingleTask& r) const
{
    return !(*this ==r);
}

SingleTask& SingleTask::operator=(SingleTask&& rr) noexcept
{
    this->_id = std::move(rr._id);
    this->_startTime = std::move(rr._startTime);
    this->_endTime =  std::move(rr._endTime);
    this->_name = std::move(rr._name);
    this->_definition = std::move(rr._definition);
    this->_isNew = std::move(rr._isNew);
    return *this;
}
