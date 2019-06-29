#include "jobpresenter.h"

JobPresenter::JobPresenter(){}

Job* JobPresenter::createJob() {
    Job* job = new Job(1, "Hola", 20, 5, time(nullptr));
    return job;
}
