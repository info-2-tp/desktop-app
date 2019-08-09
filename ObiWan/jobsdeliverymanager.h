#ifndef JOBSDELIVERYMANAGER_H
#define JOBSDELIVERYMANAGER_H

#include "jobpresenter.h"
#include "usbhandler.h"
#include "routine.h"

typedef struct {
    uint16_t type;
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
    UsbHandler* usbListener;

    QMetaObject::Connection currentConnection;

    void waitNewRoutineMessage();
    void waitRoutineSource();

};

#endif // JOBSDELIVERYMANAGER_H
