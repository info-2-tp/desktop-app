#include "routinelistener.h"

#include <QTimer>

RoutineListener::RoutineListener(){}

void RoutineListener::run() {
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(newMessage()), Qt::DirectConnection);
    timer.setInterval(5000);
    timer.start();   // puts one event in the threads event queue
    exec();
    timer.stop();
}

void RoutineListener::newMessage() {
    newRoutineSource();
}

RoutineListener::~RoutineListener() {
    this->quit();
    this->wait();
}
