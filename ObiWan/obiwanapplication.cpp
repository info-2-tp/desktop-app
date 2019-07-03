#include "obiwanapplication.h"
#include <iostream>

ObiWanApplication::ObiWanApplication(int argc, char* argv[]):  QGuiApplication (argc, argv) {}

void ObiWanApplication::terminate() {

}

void ObiWanApplication::newJob(QString name, int quantity, int size, int measure, int state, int priority, QDateTime date) {
    cout << name.toStdString() << " - " << date.toString().toStdString() << endl;
    //Job* job = this->jobPresenter.createJob();
}
