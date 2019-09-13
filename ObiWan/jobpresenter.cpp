#include "jobpresenter.h"

#include <iostream>

unsigned int min(unsigned int a, unsigned int b) {
    return a < b ? a : b;
}

unsigned int getCuts(routine_source_t source, unsigned int cutSize) {
    return source.block_count*source.block_height/cutSize;
}

unsigned int routineCants(unsigned int cuts, unsigned int blocks) {
    return cuts % blocks ? cuts/blocks + 1 : cuts/blocks;
}

routine_t buildRoutine(routine_source_t source, QList<Job> jobs, routine_source_t *remaining) {
    routine_t routine;
    if (jobs.isEmpty()) {
        remaining->block_height = 0;
        return routine;
    }
    Job job = jobs.first();
    unsigned int cuts = min(job.getRemaining_quantity(), getCuts(source, job.getHeightInMillis()));
    if (cuts == 0) {
        remaining->block_height = 0;
        return routine;
    }

    Job newJob = Job(job.getId(), job.getName(), job.getHeight(), job.getQuantity(), job.getDate(), job.getRemaining_quantity(), cuts, job.getMeasure(), IN_PROGRESS, job.getPriority());
    if (newJob.getReserved() == newJob.getRemaining_quantity()) {
        jobs.pop_front();
    }
    //TODO guardar el job
    routine.cant = routineCants(cuts, source.block_count);
    routine.height = job.getHeightInMillis();
    remaining->block_height-= routine.cant*routine.height;
    if (remaining->block_height == 0) routine.cant--;
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


//TODO estoy tiene que devolver una lista de rutinas
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
