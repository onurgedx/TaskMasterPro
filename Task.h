#ifndef TASK_H
#define TASK_H

#include <qdatetime.h>

#define SQL_SPLIT_TOOL "o-|-o"
#define NEW_TASK_NAME "new_task("+ QString::number(taskIndex)+ ")"

class SingleTask
{
private :
    int _id;
    QTime _startTime;
    QTime _endTime;
    QString _name;
    QString _definition;
    bool _isNew;
    bool _isEdit;
public:
    SingleTask(QString sqlDefinition,int id);
    SingleTask(int taskIndex);
    SingleTask(const SingleTask& r);
    SingleTask(SingleTask&& rr) noexcept;
    ~SingleTask();

    void Edit(QTime startTime , QTime endTime, QString name, QString definition);

    QTime StartTime() const;
    QTime EndTime() const;
    QString Name() const;
    QString Definition() const;
    int ID() const;
    bool IsNew() const;
    bool IsEdit() const;
    QString SQLRecord() const;

    SingleTask& operator=(const SingleTask& r);
    SingleTask& operator=(SingleTask&& rr) noexcept;
    bool operator==(const SingleTask& r) const;
    bool operator!=(const SingleTask& r) const;

};



#endif // TASK_H
