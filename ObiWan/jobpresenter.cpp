#include "jobpresenter.h"

JobPresenter::JobPresenter(JobManager& manager){
    this->manager = &manager;
}

Job* JobPresenter::createJob(string name,unsigned int quantity,unsigned int size, Measure measure, State state, Priority priority, time_t date) {
    Job* job = new Job(1, name, size, quantity, date, measure, state, priority);
    *job = repo.save(*job);
    manager->addJob(job);
    return job;
}
