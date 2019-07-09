#include "obiwanapplication.h"
#include <iostream>

ObiWanApplication::ObiWanApplication(int argc, char* argv[]): QGuiApplication (argc, argv), jobPresenter(*this) {}

void ObiWanApplication::initDb(QSqlTableModel* model, QSqlDatabase& db) {
    this->model = model;
    this->db = db;
}

QSqlTableModel& ObiWanApplication::getModel() {
    return *model;
}

void JobManager::addJob(Job* job) {
    cout << *job << endl;
    static_cast<ObiWanApplication*>(this)->getModel().select();
}

JobManager::~JobManager() {}

void ObiWanApplication::terminate() {

}

void ObiWanApplication::newJob(QString name, unsigned int quantity, unsigned int size, int measure, int state, int priority, QDateTime date) {
    this->jobPresenter.createJob(name.toStdString(), quantity, size, Measure(measure), State(state), Priority(priority), date.toTime_t());
}
