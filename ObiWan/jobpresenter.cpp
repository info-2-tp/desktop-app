#include "jobpresenter.h"

#include <iostream>

unsigned int min(unsigned int a, unsigned int b) {
    return a < b ? a : b;
}

unsigned int getCuts(routine_source_t source, unsigned int cutSize) {
    return source.block_count*(source.block_height/cutSize);
}

unsigned int routineCants(unsigned int cuts, unsigned int blocks) {
    return cuts % blocks ? cuts/blocks + 1 : cuts/blocks;
}

void JobPresenter::adjustJobs(uint32_t height, uint32_t remainder, QList<Job> &jobs) {
    for (int i = 0; i < jobs.length(); i++) {
        Job job = jobs.at(i);
        if (job.getHeightInMillis() == height && job.getRemaining_quantity() >= remainder) {
            updateJobWithNewReserved(job, job.getReserved() + remainder, jobs);
            return;
        }
    }
}

void JobPresenter::updateJobWithNewReserved(Job &job, uint32_t reserved, QList<Job> &jobs) {
    Job newJob = Job(job.getId(), job.getName(), job.getHeight(), job.getQuantity(), job.getDate(), job.getRemaining_quantity(), reserved, job.getMeasure(), IN_PROGRESS, job.getPriority());
    if (newJob.getReserved() == newJob.getRemaining_quantity()) {
        jobs.pop_front();
    } else {
        jobs.replace(jobs.indexOf(job), newJob);
    }

    repo.update(newJob);
}

bool JobPresenter::buildRoutine(routine_source_t source, QList<Job> &jobs, routine_source_t *remaining, routine_t *routine) {
    if (jobs.isEmpty()) {
        return false;
    }
    Job job = jobs.first();
    unsigned int cuts = min(job.getAvailable_quantity(), getCuts(source, job.getHeightInMillis()));
    if (cuts == 0) {
        jobs.pop_front();
        return buildRoutine(source, jobs, remaining, routine);
    }
    updateJobWithNewReserved(job, job.getReserved() + cuts, jobs);

    routine->cant = routineCants(cuts, source.block_count);
    routine->height = job.getHeightInMillis();

    uint32_t remainder = routine->cant*source.block_count - cuts;

    if (remainder) {
        adjustJobs(routine->height, remainder, jobs);
    }
    remaining->block_height-= routine->cant*routine->height;
    if (remaining->block_height == 0) routine->cant--;
    return true;
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

void JobPresenter::revertOldRoutines() {
    repo.revertInProgress();
    manager->refreshJobs();
}


QList<routine_t> JobPresenter::getRoutine(routine_source_t source) {
    QList<routine_t> routines = QList<routine_t>();
    routine_source_t remaining;
    remaining.block_count = source.block_count;
    remaining.block_height = source.block_height;
    cout << "get routine for " << +source.block_count << " bloques, de " << source.block_height << " milimetros" << endl;
    QList<Job> jobs = repo.findPriorizedWithState(READY);
    bool shouldContinue = true;
    while(shouldContinue && !jobs.isEmpty()) {
        routine_t routine;
        shouldContinue = buildRoutine(remaining, jobs, &remaining, &routine);
        if (shouldContinue) {
            routines.append(routine);
            cout << "routine: " << +routine.cant << " vueltas de tamaño " << routine.height << " milimetros" << endl;
        }
    }
    manager->refreshJobs();
    return routines;
}
