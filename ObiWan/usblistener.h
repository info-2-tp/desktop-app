#ifndef ROUTINELISTENER_H
#define ROUTINELISTENER_H

#include <QThread>

class UsbListener: public QThread
{
    Q_OBJECT
signals:
    void newMessage();
private:
    void* buffer;
    uint16_t size;

    void run();
private slots:
    void listen();
public:
    UsbListener(void *buffer, uint16_t size);
    ~UsbListener();
};

#endif // ROUTINELISTENER_H
