#ifndef JOBPRESENTER_H
#define JOBPRESENTER_H

#include "job.h"
#include "jobrepository.h"
#include "routine.h"

using namespace std;

class JobManager {
public:
    virtual void refreshJobs();
    virtual void r2d2IsCutting(unsigned int cube_size);
    virtual void newCut(uint16_t cut_size);
    virtual void ack();
    virtual ~JobManager();
};

class JobPresenter {
private:
    JobManager* manager;
    JobRepository repo;
    bool buildRoutine(routine_source_t source, QList<Job> &jobs, routine_source_t *remaining, routine_t *routine);
    void updateJobWithNewReserved(Job &job, uint32_t reserved, QList<Job> &jobs);
    void adjustJobs(uint32_t height, uint32_t remainder, QList<Job> &jobs);
public:
    JobPresenter(JobManager& manager);

    Job* createJob(string name, unsigned int quantity, unsigned int size, Measure measure, State state, Priority priority, time_t date);

    QList<routine_t> getRoutine(routine_source_t source);
    void revertOldRoutines();
    void successInProgressJobs();
    void r2d2Working(unsigned int cube_size);
    void cut(uint16_t cut_size);

};

#endif // JOBPRESENTER_H
