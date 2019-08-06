#include <QSettings>
#include "usbhandler.h"
#include <iostream>

using namespace std;

#define DEFAULT_INTERFACE 1
#define DEFAULT_IN_ENDPOINT 0x83

#define KERNEL_DRIVER_IS_ACTIVE 1
#define SUCCESS 0

UsbHandler::UsbHandler(){
    configure();
    initializeUsb();
}

void UsbHandler::configure() {
    settingsFileName = ":/config.ini";
    QSettings settings(settingsFileName, QSettings::IniFormat);
    vendor_id = settings.value("usb/VendorID", "default").toInt();
    product_id = settings.value("usb/ProductID", "default").toInt();
}

void UsbHandler::initializeUsb() {
    libusb_device **devices;
    int results;
    ssize_t devices_size;
    results = libusb_init(&context);
    if(results != LIBUSB_SUCCESS) {
        cout<<"Init Error "<< results << endl;
        exit(1);
    }

    libusb_set_option(context, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_INFO);
    devices_size = libusb_get_device_list(context, &devices);
    if(devices_size < SUCCESS) {
        cout << "Get Device Error" <<endl;
        exit(1);
    }

    device = searchDevice(devices, devices_size);

    if (device == nullptr) {
        cout << "No se encontró el dispositivo conectado." <<endl;
        libusb_free_device_list(devices, 1);
        exit(1);
    }
    libusb_device_descriptor device_descriptor;
    libusb_get_device_descriptor(device, &device_descriptor);

    cout<<"VendorID: "<<device_descriptor.idVendor<<"  ";
    cout<<"ProductID: "<<device_descriptor.idProduct<< "  ";
    libusb_config_descriptor *config;
    libusb_get_config_descriptor(device, 0, &config);
    cout<<"Interfaces: "<<static_cast<int>(config->bNumInterfaces)<< endl;

    device_hundler = libusb_open_device_with_vid_pid(context, vendor_id, product_id);

    if(device_hundler == nullptr){
        cout<<"Cannot open device"<<endl;
        libusb_free_device_list(devices, 1);
        exit(1);
    }
    cout<<"Device Opened"<<endl;
    libusb_free_device_list(devices, 1);
}

libusb_device* UsbHandler::searchDevice(libusb_device** devices, ssize_t size) {
    for(ssize_t i = 0; i < size; i++) {
        libusb_device_descriptor desc;
        if (libusb_get_device_descriptor(devices[i], &desc) < 0) {
            cout<<"failed to get device descriptor"<<endl;
            exit(1);
        }
        if (desc.idVendor == vendor_id && desc.idProduct == product_id) return devices[i];
    }
    return nullptr;
}

void UsbHandler::listen(void *buffer, uint16_t size) {
    this->buffer = buffer;
    this->size = size;
    this->start();
}

void UsbHandler::prepareDevice() {
    if(libusb_kernel_driver_active(device_hundler, DEFAULT_INTERFACE) == KERNEL_DRIVER_IS_ACTIVE) { //find out if kernel driver is attached
        cout<<"Kernel Driver Active"<<endl;
        if(libusb_detach_kernel_driver(device_hundler, DEFAULT_INTERFACE) == SUCCESS) //detach it
            cout<<"Kernel Driver Detached!"<<endl;
        else {
            cout<<"Kernel Driver is not Detached!"<<endl;
            exit(1);
        }
    }
    int i = libusb_claim_interface(device_hundler, DEFAULT_INTERFACE);
    if (i != SUCCESS) {
        cout<<"Fails to claim interface "<< i << endl;
        libusb_release_interface(device_hundler, DEFAULT_INTERFACE);
        libusb_claim_interface(device_hundler, DEFAULT_INTERFACE);
    }

    //TODO sacar a una funcion
    libusb_config_descriptor *config;
    libusb_get_config_descriptor(device, 0, &config);
    const libusb_interface *interface;
    const libusb_interface_descriptor *interface_descriptor;
    const libusb_endpoint_descriptor *endpoint_descriptor;
    cout << "Interfaces: " << config->bNumInterfaces << endl;
    for (int i = 0; i < config->bNumInterfaces; i++) {
        interface = &config->interface[i];
        cout << "Interface " << i << endl;
        cout<<"\tNumber of alternate settings: "<<interface->num_altsetting<<endl;
        for(int j=0; j<interface->num_altsetting; j++) {
            interface_descriptor = &interface->altsetting[j];
            cout << "\tSetting " << j << endl;
            cout<<"\t\tInterface Number: "<<static_cast<int>(interface_descriptor->bInterfaceNumber)<<endl;
            cout<<"\t\tNumber of endpoints: "<<static_cast<int>(interface_descriptor->bNumEndpoints)<<endl;
            for(int k=0; k<static_cast<int>(interface_descriptor->bNumEndpoints); k++) {
                endpoint_descriptor = &interface_descriptor->endpoint[k];
                cout << "\t\t\tEndpoint " << k << " -> ";
                cout<<"Descriptor Type: "<<static_cast<int>(endpoint_descriptor->bDescriptorType)<<" | ";
                cout<<"EP Address: "<<static_cast<int>(endpoint_descriptor->bEndpointAddress)<<endl;
            }
        }
    }
    cout<<endl<<endl<<endl;
    libusb_free_config_descriptor(config);
}

void UsbHandler::run() {
    prepareDevice();
    int bytes = 0;
    while (bytes != size) {
        int hasError = libusb_interrupt_transfer(device_hundler, DEFAULT_IN_ENDPOINT, static_cast<uint8_t*>(buffer), size, &bytes, 0);
        cout << "Bytes: " << bytes << endl << "|" << +static_cast<uint8_t*>(buffer)[0] <<
                "|" << +static_cast<uint8_t*>(buffer)[1] <<
                "|" << +static_cast<uint8_t*>(buffer)[2] <<
                "|" << +static_cast<uint8_t*>(buffer)[3] << "|" << endl;
        if (!hasError && bytes == size) newMessage();
    }

}

UsbHandler::~UsbHandler() {
    if (this->isRunning()) {
        this->quit();
        this->wait();
    }
    cout<<"Released USB Interface"<<endl;
    libusb_release_interface(device_hundler, DEFAULT_INTERFACE);
    libusb_close(device_hundler); //close the device we opened
    libusb_exit(context);
}
