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

private:
    bool insert(Job job);
};

#endif // JOBREPOSITORY_H
