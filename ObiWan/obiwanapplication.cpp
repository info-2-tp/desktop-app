#include "obiwanapplication.h"
#include <iostream>

ObiWanApplication::ObiWanApplication(int argc, char* argv[]):  QGuiApplication (argc, argv) {}

void ObiWanApplication::terminate() {

}

void ObiWanApplication::newJob(QString name, unsigned int quantity, unsigned int size, int measure, int state, int priority, QDateTime date) {

    Job* job = this->jobPresenter.createJob(name.toStdString(), quantity, size, Measure(measure), State(state), Priority(priority), date.toTime_t());
    cout << job->toString() << endl;
}
