#include "jobpresenter.h"

#include <iostream>

JobPresenter::JobPresenter(JobManager& manager) {
    this->manager = &manager;
}

Job* JobPresenter::createJob(string name,unsigned int quantity,unsigned int size, Measure measure, State state, Priority priority, time_t date) {
    Job* job = new Job(name, size, quantity, date, measure, state, priority);
    *job = repo.save(*job);
    manager->refreshJobs();
    return job;
}

routine_t JobPresenter::getRoutine(routine_source_t source) {
    routine_t routine;
    cout << "get routine for " << +source.block_count << " bloques, de " << source.block_height << " milimetros" << endl;
    repo.findPriorizedWithState(READY);
    return routine;
}
