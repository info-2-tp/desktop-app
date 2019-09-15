#ifndef JOBPRESENTER_H
#define JOBPRESENTER_H

#include "job.h"
#include "jobrepository.h"
#include "routine.h"

using namespace std;

class JobManager {
public:
    virtual void refreshJobs();
    virtual ~JobManager();
};

class JobPresenter {
private:
    JobManager* manager;
    JobRepository repo;
    routine_t buildRoutine(routine_source_t source, QList<Job> &jobs, routine_source_t *remaining);

public:
    JobPresenter(JobManager& manager);

    Job* createJob(string name, unsigned int quantity, unsigned int size, Measure measure, State state, Priority priority, time_t date);

    QList<routine_t> getRoutine(routine_source_t source);

};

#endif // JOBPRESENTER_H
