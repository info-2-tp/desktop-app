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
    Q_PROPERTY(int cubeSize READ getNewCubeSize WRITE setNewCubeSize NOTIFY newCubePrepare)
    Q_PROPERTY(int cutSize READ getCutSize WRITE setCutSize NOTIFY newCut)
    Q_PROPERTY(void newAck NOTIFY newAck)
public:
    explicit ObiWanApplication(int argc, char* argv[]);
    void initDb(QSqlTableModel* model, QSqlDatabase& db);
    void new_cube(unsigned int cube_size);
    void terminate();
    void setNewCubeSize(int cubeSize);
    int getNewCubeSize();
    void new_cut(uint16_t cut_size);
    void setCutSize(int cutSize);
    int getCutSize();

    void new_ack();


signals:
    void newCubePrepare(int cubeSize);
    void newCut(int cutSize);
    void newAck();

public slots:
    void newJob(QString name, unsigned int quantity, unsigned int size, int measure, int state, int priority, QDateTime date);
    QSqlTableModel& getModel();

private:
    QSqlDatabase db;
    QSqlTableModel* model;
    JobPresenter jobPresenter;
    JobsDeliveryManager* deliveryManager;
    unsigned int cubeSize;
    uint16_t cutSize;

};

#endif // OBIWANAPPLICATION_H
