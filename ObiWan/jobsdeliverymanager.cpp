#include "jobsdeliverymanager.h"

#include <QTimer>

JobsDeliveryManager::JobsDeliveryManager(JobPresenter* jobPresenter)
{
    this->jobPresenter = jobPresenter;
    this->routineListener = new RoutineListener();
    QObject::connect((this->routineListener), SIGNAL(newRoutineSource()), this, SLOT(newMessage()), Qt::QueuedConnection);
    this->routineListener->start();
}

void JobsDeliveryManager::newMessage() {
    routine_source_t source;
    source.block_count = 3;
    source.block_height = 500;
    jobPresenter->getRoutine(source);
}

JobsDeliveryManager::~JobsDeliveryManager() {
    delete this->routineListener;
}
