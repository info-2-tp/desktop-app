#include "obiwanapplication.h"
#include <iostream>

ObiWanApplication::ObiWanApplication(int argc, char* argv[]): QGuiApplication (argc, argv), jobPresenter(*this) {
    this->deliveryManager = new JobsDeliveryManager(&jobPresenter);
    settingsFileName = ":/config.ini";
    cout << settingsFileName.toStdString() << endl;
    QSettings settings(settingsFileName, QSettings::IniFormat);
    QString sText = settings.value("usb/VendorID", "default").toString();
    cout << sText.toStdString() << endl;
}

void ObiWanApplication::initDb(QSqlTableModel* model, QSqlDatabase& db) {
    this->model = model;
    this->db = db;
}

QSqlTableModel& ObiWanApplication::getModel() {
    return *model;
}

void JobManager::refreshJobs() {
    static_cast<ObiWanApplication*>(this)->getModel().select();
}

JobManager::~JobManager() {}

void ObiWanApplication::terminate() {
    delete deliveryManager;
    delete model;
}

void ObiWanApplication::newJob(QString name, unsigned int quantity, unsigned int size, int measure, int state, int priority, QDateTime date) {
    this->jobPresenter.createJob(name.toStdString(), quantity, size, Measure(measure), State(state), Priority(priority), date.toTime_t());
}
