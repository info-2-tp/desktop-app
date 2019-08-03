#ifndef JOBSDELIVERYMANAGER_H
#define JOBSDELIVERYMANAGER_H

#include "jobpresenter.h"
#include "usblistener.h"

using namespace std;

class JobsDeliveryManager : public QObject
{
    Q_OBJECT
public:
    JobsDeliveryManager(JobPresenter* jobPresenter);
    ~JobsDeliveryManager();

public slots:
        void newMessage();
private:
    JobPresenter* jobPresenter;
    UsbListener* routineListener;
};

#endif // JOBSDELIVERYMANAGER_H
