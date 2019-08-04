#ifndef ROUTINELISTENER_H
#define ROUTINELISTENER_H

#include <QThread>

class UsbHandler: public QThread
{
    Q_OBJECT
signals:
    void newMessage();
private:
    void* buffer;
    uint16_t size;

    void run();
private slots:
    void listenTimer();
public:
    UsbHandler();
    ~UsbHandler();

    void listen(void* buffer, uint16_t size);

};

#endif // ROUTINELISTENER_H
