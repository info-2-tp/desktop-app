#include "jobsdeliverymanager.h"

#include <iostream>

JobsDeliveryManager::JobsDeliveryManager(JobPresenter* jobPresenter)
{
    cout << "Sizeof de message_header_t: " << sizeof (message_header_t) << endl;
    cout << "Sizeof de routine_source_t: " << sizeof (routine_source_t) << endl;
    this->jobPresenter = jobPresenter;
    this->usbListener = createNewRoutineListener();
}

UsbListener* JobsDeliveryManager::createNewRoutineListener() {
    UsbListener* listener = new UsbListener(&header, sizeof (message_header_t));
    QObject::connect(listener, SIGNAL(newMessage()), this, SLOT(newRoutineRequestHeader()), Qt::QueuedConnection);
    listener->start();
    return listener;
}

UsbListener* JobsDeliveryManager::createRoutineSourceListener() {
    UsbListener* listener = new UsbListener(&routine_source, sizeof (routine_source_t));
    QObject::connect(listener, SIGNAL(newMessage()), this, SLOT(newRoutineRequest()), Qt::QueuedConnection);
    listener->start();
    return listener;
}

void JobsDeliveryManager::newRoutineRequestHeader() {
    cout << "Header -> tipo: " << +header.type << " tamaño: " << header.size << endl;
    /*
    routine_source_t source;
    source.block_count = 3;
    source.block_height = 500;
    jobPresenter->getRoutine(source);
    */
    delete usbListener;
    usbListener = createRoutineSourceListener();
}

void JobsDeliveryManager::newRoutineRequest() {
    cout << "Bloques: " << +routine_source.block_count << " tamaño: " << routine_source.block_height << endl;
    this->jobPresenter->getRoutine(routine_source);
    delete usbListener;
    usbListener = createNewRoutineListener();
}

JobsDeliveryManager::~JobsDeliveryManager() {
    delete this->usbListener;
}
