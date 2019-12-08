#include "obiwanapplication.h"
#include <iostream>

ObiWanApplication::ObiWanApplication(int argc, char* argv[]): QGuiApplication (argc, argv), jobPresenter(*this) {
    this->deliveryManager = new JobsDeliveryManager(&jobPresenter);
}

void ObiWanApplication::initDb(QSqlTableModel* model, QSqlDatabase& db) {
    this->model = model;
    this->db = db;
}

void ObiWanApplication::new_cube(unsigned int cube_size) {
    this->setNewCubeSize(cube_size);
    this->newCubePrepare(cube_size);
}

void ObiWanApplication::new_cut(uint16_t cut_size) {
    this->setCutSize(cut_size);
    this->newCut(cut_size);
}

void ObiWanApplication::new_ack() {
    this->newAck();
}

void ObiWanApplication::setNewCubeSize(int cubeSize) {
    this->cubeSize = cubeSize;
}

void ObiWanApplication::setCutSize(int cutSize) {
    this->cutSize = cutSize;
}

int ObiWanApplication::getNewCubeSize() {
    return this->cubeSize;
}

int ObiWanApplication::getCutSize() {
    return this->cutSize;
}

QSqlTableModel& ObiWanApplication::getModel() {
    return *model;
}

void JobManager::refreshJobs() {
    static_cast<ObiWanApplication*>(this)->getModel().select();
}

void JobManager::r2d2IsCutting(unsigned int cube_size) {
    cout << "Cortando cubo de " << cube_size << " milimetros" << endl;
    static_cast<ObiWanApplication*>(this)->new_cube(cube_size);
}

void JobManager::newCut(uint16_t cut_size){
    cout << "Nuevo Corte de " << cut_size << " milimetros" << endl;
    static_cast<ObiWanApplication*>(this)->new_cut(cut_size);
}

void JobManager::ack(){
    static_cast<ObiWanApplication*>(this)->new_ack();
}

JobManager::~JobManager() {}

void ObiWanApplication::terminate() {
    delete deliveryManager;
    delete model;
}

void ObiWanApplication::newJob(QString name, unsigned int quantity, unsigned int size, int measure, int state, int priority, QDateTime date) {
    this->jobPresenter.createJob(name.toStdString(), quantity, size, Measure(measure), State(state), Priority(priority), date.toTime_t());
}
