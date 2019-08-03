#include "usblistener.h"

#include <QTimer>

UsbListener::UsbListener(){}

void UsbListener::run() {
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(newMessage()), Qt::DirectConnection);
    timer.setInterval(5000);
    timer.start();   // puts one event in the threads event queue
    exec();
    timer.stop();
}

void UsbListener::newMessage() {
    newRoutineSource();
}

UsbListener::~UsbListener() {
    this->quit();
    this->wait();
}
