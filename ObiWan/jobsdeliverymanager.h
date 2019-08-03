#ifndef JOBSDELIVERYMANAGER_H
#define JOBSDELIVERYMANAGER_H

#include "jobpresenter.h"
#include "usblistener.h"
#include "routine.h"

typedef struct {
    uint8_t type;
    uint16_t size;
} message_header_t;

using namespace std;

class JobsDeliveryManager : public QObject
{
    Q_OBJECT
public:
    JobsDeliveryManager(JobPresenter* jobPresenter);
    ~JobsDeliveryManager();

public slots:
        void newRoutineRequestHeader();
        void newRoutineRequest();
private:
    message_header_t header;
    routine_source_t routine_source;

    JobPresenter* jobPresenter;
    UsbListener* usbListener;

    UsbListener* createNewRoutineListener();
    UsbListener* createRoutineSourceListener();

};

#endif // JOBSDELIVERYMANAGER_H
