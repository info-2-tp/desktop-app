#ifndef JOBREPOSITORY_H
#define JOBREPOSITORY_H

#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>

#include "job.h"

#define ID 0
#define NEW_ID(id) id + 1

class JobRepository
{
public:
    JobRepository();
    Job save(Job job);
    Job update(Job job);
    QList<Job> findPriorizedWithState(State state);
    void revertInProgress();

private:
    bool insert(Job job);
    Job parseQueryResult(QSqlQuery query);
};

#endif // JOBREPOSITORY_H
