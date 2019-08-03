#ifndef ROUTINELISTENER_H
#define ROUTINELISTENER_H

#include <QThread>

class UsbListener: public QThread
{
    Q_OBJECT
signals:
    void newRoutineSource( );
private:
    void run();
private slots:
    void newMessage();
public:
    UsbListener();
    ~UsbListener();
};

#endif // ROUTINELISTENER_H
