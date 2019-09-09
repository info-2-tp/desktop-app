#include "jobpresenter.h"

#include <iostream>

unsigned int getCuts(routine_source_t source, unsigned int cutSize) {
    return source.block_count*source.block_height/cutSize;
}

routine_t buildRoutine(routine_source_t source, QList<Job> jobs, routine_source_t *remaining) {
    routine_t routine;
    Job job = jobs.first();
    unsigned int cuts = getCuts(source, job.getHeightInMillis());
    return routine;
}

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
    routine_source_t remaining;
    remaining.block_count = source.block_count;
    remaining.block_height = source.block_height;
    routine_t routine;
    cout << "get routine for " << +source.block_count << " bloques, de " << source.block_height << " milimetros" << endl;
    QList<Job> jobs = repo.findPriorizedWithState(READY);

    while(remaining.block_height > 0) {
        routine = buildRoutine(remaining, jobs, &remaining);
    }
    return routine;
}
