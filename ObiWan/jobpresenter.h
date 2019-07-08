#ifndef JOBPRESENTER_H
#define JOBPRESENTER_H

#include "job.h"
#include "jobrepository.h"

using namespace std;

class JobManager {
public:
    virtual void addJob(Job* job);
    virtual ~JobManager();
};

class JobPresenter {
private:
    JobManager* manager;
    JobRepository repo;

public:
    JobPresenter(JobManager& manager);

    Job* createJob(string name, unsigned int quantity, unsigned int size, Measure measure, State state, Priority priority, time_t date);
};

#endif // JOBPRESENTER_H
