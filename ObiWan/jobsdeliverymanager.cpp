#include "jobsdeliverymanager.h"

#include <iostream>

JobsDeliveryManager::JobsDeliveryManager(JobPresenter* jobPresenter)
{
    this->jobPresenter = jobPresenter;
    this->usbListener = new UsbHandler();
    this->waitNewRoutineMessage();
}

void JobsDeliveryManager::waitNewRoutineMessage() {
    this->currentConnection = QObject::connect(this->usbListener, SIGNAL(newMessage()), this, SLOT(newRoutineRequestHeader()), Qt::QueuedConnection);
    this->usbListener->listen(&header, sizeof (message_header_t));
}

void JobsDeliveryManager::waitRoutineSource() {
    this->currentConnection = QObject::connect(this->usbListener, SIGNAL(newMessage()), this, SLOT(newRoutineRequest()), Qt::QueuedConnection);
    this->usbListener->listen(&routine_source, sizeof (routine_source_t));
}

void JobsDeliveryManager::newRoutineRequestHeader() {
    QObject::disconnect(this->currentConnection);
    cout << "Header -> tipo: " << +header.type << " tamaño: " << header.size << endl;
    //this->waitRoutineSource();
    //TODO solo para probar el header
    this->waitNewRoutineMessage();
}

void JobsDeliveryManager::newRoutineRequest() {
    QObject::disconnect(this->currentConnection);
    cout << "Bloques: " << +routine_source.block_count << " tamaño: " << routine_source.block_height << endl;
    this->jobPresenter->getRoutine(routine_source);
    this->waitNewRoutineMessage();
}

JobsDeliveryManager::~JobsDeliveryManager() {
    delete this->usbListener;
}
