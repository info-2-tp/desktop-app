#ifndef OBIWANAPPLICATION_H
#define OBIWANAPPLICATION_H

#include <QGuiApplication>
#include <QDateTime>

#include "jobpresenter.h"
#include "job.h"

using namespace std;

class ObiWanApplication: public QGuiApplication, public JobManager
{
    Q_OBJECT
public:
    explicit ObiWanApplication(int argc, char* argv[]);

    void terminate();

public slots:
    void newJob(QString name, unsigned int quantity, unsigned int size, int measure, int state, int priority, QDateTime date);

private:
    JobPresenter jobPresenter;
};

#endif // OBIWANAPPLICATION_H
