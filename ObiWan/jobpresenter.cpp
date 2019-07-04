#include "jobpresenter.h"

JobPresenter::JobPresenter(JobManager& manager){
    this->manager = &manager;
}

Job* JobPresenter::createJob(string name,unsigned int quantity,unsigned int size, Measure measure, State state, Priority priority, time_t date) {
    Job* job = new Job(1, name, size, quantity, date, measure, state, priority);
    /* TODO Acá deberia persistirse en la base de datos */
    manager->addJob(job);
    return job;
}
