#ifndef OBIWANAPPLICATION_H
#define OBIWANAPPLICATION_H

#include <QGuiApplication>
#include <QDateTime>

#include "jobpresenter.h"

using namespace std;

class ObiWanApplication: public QGuiApplication
{
    Q_OBJECT
public:
    explicit ObiWanApplication(int argc, char* argv[]);

    void terminate();

public slots:
    void newJob(QString name, int quantity, int size, int measure, int state, int priority, QDateTime date);

private:
    JobPresenter jobPresenter;
};

#endif // OBIWANAPPLICATION_H
