#include <QSettings>
#include "usbhandler.h"
#include <iostream>

using namespace std;

#define ALLWAYS true
#define CONFIG_FILE ":/config.ini"
#define SERIAL_PORT_NAME "usb/serialPort"
#define BAUD_RATE_NAME "usb/baudRate"

UsbHandler::UsbHandler(){
    configure();
    start();
}

void UsbHandler::configure() {
    QSettings settings(CONFIG_FILE, QSettings::IniFormat);
    serialPort.setPortName(settings.value(SERIAL_PORT_NAME).toString());
    serialPort.setBaudRate(settings.value(BAUD_RATE_NAME).toInt());
    if (!serialPort.open(QIODevice::ReadOnly)) {
            cout << QObject::tr("Failed to open, error: %1").arg(serialPort.error()).toStdString() << endl;
    }
}

void UsbHandler::listen(void *buffer, uint16_t size) {
    this->buffer = buffer;
    this->size = size;
    this->loading = true;
}

void UsbHandler::run() {
    while(ALLWAYS) {
        if (loading) read();
    }
}

void UsbHandler::read() {
    qint64 readedBytes = serialPort.read(static_cast<char*>(buffer), size);
    while (readedBytes < size) {
        serialPort.waitForReadyRead();
        readedBytes+= serialPort.read(static_cast<char*>(buffer) + readedBytes, size - readedBytes);
    }
    loading = false;
    newMessage();
}

UsbHandler::~UsbHandler() {
    if (this->isRunning()) {
        this->quit();
        this->wait();
    }
}
