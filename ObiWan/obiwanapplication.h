#ifndef OBIWANAPPLICATION_H
#define OBIWANAPPLICATION_H

#include <QGuiApplication>

#include "jobpresenter.h"

class ObiWanApplication: public QGuiApplication
{
    Q_OBJECT
public:
    explicit ObiWanApplication(int argc, char* argv[]);

    void terminate();

public slots:
    void newJob();

private:
    JobPresenter jobPresenter;
};

#endif // OBIWANAPPLICATION_H
