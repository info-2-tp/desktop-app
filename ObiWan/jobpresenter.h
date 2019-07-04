#ifndef JOBPRESENTER_H
#define JOBPRESENTER_H

#include "job.h"

using namespace std;

class JobPresenter {
public:
    JobPresenter();

    Job* createJob(string name, unsigned int quantity, unsigned int size, Measure measure, State state, Priority priority, time_t date);
};

#endif // JOBPRESENTER_H
