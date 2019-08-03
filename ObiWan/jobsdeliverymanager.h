#ifndef JOBSDELIVERYMANAGER_H
#define JOBSDELIVERYMANAGER_H

#include "jobpresenter.h"

using namespace std;

class JobsDeliveryManager
{
public:
    JobsDeliveryManager(JobPresenter* jobPresenter);

private:
    JobPresenter* jobPresenter;
};

#endif // JOBSDELIVERYMANAGER_H
