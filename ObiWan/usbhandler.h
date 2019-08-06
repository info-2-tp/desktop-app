#ifndef ROUTINELISTENER_H
#define ROUTINELISTENER_H

using namespace std;
#include <QThread>
#include <libusb.h>

class UsbHandler: public QThread
{
    Q_OBJECT
signals:
    void newMessage();
private:
    void* buffer;
    uint16_t size;

    QString settingsFileName;
    uint16_t vendor_id;
    uint16_t product_id;

    libusb_device* device;
    libusb_context *context = nullptr;
    libusb_device_handle *device_hundler;

    void run();
    void configure();
    void initializeUsb();
    libusb_device* searchDevice(libusb_device** devices, ssize_t size);
    void prepareDevice();
public:
    UsbHandler();
    ~UsbHandler();

    void listen(void* buffer, uint16_t size);

};

#endif // ROUTINELISTENER_H
