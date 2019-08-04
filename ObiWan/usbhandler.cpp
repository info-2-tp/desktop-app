#include "usbhandler.h"

#include <QTimer>

//Borrar
#include "routine.h"
typedef struct {
    uint8_t type;
    uint16_t size;
} message_header_t;

UsbHandler::UsbHandler(){}

void UsbHandler::listen(void *buffer, uint16_t size) {
    this->buffer = buffer;
    this->size = size;
    this->start();
}

void UsbHandler::run() {
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(listenTimer()), Qt::DirectConnection);
    timer.setInterval(5000);
    timer.start();   // puts one event in the threads event queue
    exec();
    timer.stop();
}

void UsbHandler::listenTimer() {
    if (size == sizeof (message_header_t)) {
        message_header_t* header = (message_header_t*)buffer;
        header->type = ROUTINE_SOURCE_MESSAGE;
        header->size = sizeof (routine_source_t);
    }
    if (size == sizeof (routine_source_t)) {
        routine_source_t* source = (routine_source_t*)buffer;
        source->block_count = 3;
        source->block_height = 500;
    }
    this->quit();
    newMessage();
}

UsbHandler::~UsbHandler() {
    if (this->isRunning()) {
        this->quit();
        this->wait();
    }
}
