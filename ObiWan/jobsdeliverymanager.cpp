#include "jobsdeliverymanager.h"

#include <iostream>

routine_t* buildRoutines(QList<routine_t> routineList) {
    routine_t* routines = static_cast<routine_t*>(calloc(routineList.length(), sizeof (routine_t)));
    for (int i = 0; i < routineList.size(); i++) {
        routines[i] = routineList.at(i);
    }
    return routines;
}

JobsDeliveryManager::JobsDeliveryManager(JobPresenter* jobPresenter)
{
    this->jobPresenter = jobPresenter;
    this->usbListener = new UsbHandler();
    this->waitMessageHeader();
}

void JobsDeliveryManager::waitMessageHeader() {
    this->currentConnection = QObject::connect(this->usbListener, SIGNAL(newMessage()), this, SLOT(newMessageHeader()), Qt::QueuedConnection);
    this->usbListener->listen(&header, sizeof (message_header_t));
}

void JobsDeliveryManager::waitRoutineSource() {
    this->currentConnection = QObject::connect(this->usbListener, SIGNAL(newMessage()), this, SLOT(newRoutineRequest()), Qt::QueuedConnection);
    this->usbListener->listen(&routine_source, sizeof (routine_source_t));
}

void JobsDeliveryManager::waitCut() {
    this->currentConnection = QObject::connect(this->usbListener, SIGNAL(newMessage()), this, SLOT(newCut()), Qt::QueuedConnection);
    this->usbListener->listen(&cut_size, sizeof (cut_size));
}

void JobsDeliveryManager::newMessageHeader() {
    QObject::disconnect(this->currentConnection);
    cout << "Header -> tipo: " << +header.type << " tamaño: " << header.size << endl;
    if (ROUTINE_SOURCE_MESSAGE == header.type) this->waitRoutineSource();
    if (ACK == header.type) this->ack();
    if (PING == header.type) this->pong();
    if (CUT_MESSAGE == header.type) this->waitCut();
}

void JobsDeliveryManager::newRoutineRequest() {
    QObject::disconnect(this->currentConnection);
    cout << "Bloques: " << +routine_source.block_count << " tamaño: " << routine_source.block_height << endl;
    this->jobPresenter->r2d2Working(routine_source.block_height);
    revertOldRoutines();
    QList<routine_t> routineList = this->jobPresenter->getRoutine(routine_source);
    routine_t* routines = buildRoutines(routineList);
    message_header_t header;
    header.type = ROUTINE_MESSAGE;
    header.size = sizeof(routine_t)*static_cast<uint16_t>(routineList.length());
    this->usbListener->send(&header, sizeof (header));
    this->usbListener->send(routines, header.size);
    free(routines);
    this->waitMessageHeader();
}

void JobsDeliveryManager::newCut() {
    QObject::disconnect(this->currentConnection);
    this->jobPresenter->cut(cut_size);
    this->waitMessageHeader();
}

void JobsDeliveryManager::revertOldRoutines() {
    this->jobPresenter->revertOldRoutines();
}

void JobsDeliveryManager::ack() {
    cout << "Recibiendo ACK" << endl;
    this->jobPresenter->successInProgressJobs();
    this->waitMessageHeader();
}

void JobsDeliveryManager::pong() {
    cout << "Recibiendo PING" << endl;
    message_header_t header;
    header.type = PONG;
    header.size = 0;
    this->usbListener->send(&header, sizeof (header));
    this->waitMessageHeader();
}

JobsDeliveryManager::~JobsDeliveryManager() {
    delete this->usbListener;
}
