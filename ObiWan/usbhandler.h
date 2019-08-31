#ifndef ROUTINELISTENER_H
#define ROUTINELISTENER_H

using namespace std;
#include <QThread>
#include <QtSerialPort>

class UsbHandler: public QThread
{
    Q_OBJECT
signals:
    void newMessage();
private:
    void* buffer;
    uint16_t size;
    bool loading;

    QSerialPort serialPort;

    void run();
    void configure();
    void read();
public:
    UsbHandler();
    ~UsbHandler();

    void listen(void* buffer, uint16_t size);
};

#endif // ROUTINELISTENER_H
