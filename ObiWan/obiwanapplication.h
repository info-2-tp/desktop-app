#ifndef OBIWANAPPLICATION_H
#define OBIWANAPPLICATION_H

#include <QGuiApplication>
#include <QDateTime>
#include <QtWidgets>
#include <QtSql>

#include "jobpresenter.h"
#include "job.h"
#include "jobsdeliverymanager.h"

using namespace std;

class ObiWanApplication: public QGuiApplication, public JobManager
{
    Q_OBJECT
public:
    explicit ObiWanApplication(int argc, char* argv[]);
    void initDb(QSqlTableModel* model, QSqlDatabase& db);
    void terminate();

public slots:
    void newJob(QString name, unsigned int quantity, unsigned int size, int measure, int state, int priority, QDateTime date);
    QSqlTableModel& getModel();

private:
    QSqlDatabase db;
    QSqlTableModel* model;
    JobPresenter jobPresenter;
    JobsDeliveryManager* deliveryManager;

};

#endif // OBIWANAPPLICATION_H
