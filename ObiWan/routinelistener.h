#ifndef ROUTINELISTENER_H
#define ROUTINELISTENER_H

#include <QThread>

class RoutineListener: public QThread
{
    Q_OBJECT
signals:
    void newRoutineSource( );
private:
    void run();
private slots:
    void newMessage();
public:
    RoutineListener();
    ~RoutineListener();
};

#endif // ROUTINELISTENER_H
