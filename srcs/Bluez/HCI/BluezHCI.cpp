#include <sys/ioctl.h>
#include <strings.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include "Bluez/HCI/BluezHCI.hpp"

//
// PUBLIC
//

BluezHCI                            *BluezHCI::Instance()
{
    static BluezHCI                 BluezHCI;

    return &BluezHCI;
}

void                                *BluezHCI::getHCIPacket()
{
    // TODO, implement... return type won't be (void *) type
    return nullptr;
}

int                                 BluezHCI::getBluetoothAddressBy(int interfaceId, BluetoothAddress &address) const
{
    int                 devDesc;
    struct hci_dev_info devInfo = { // This struct contains information about a given adapter
        .dev_id = (uint16_t)interfaceId       // devId == interfaceId == hci_dev
    }; 
    struct sockaddr_hci sockAddr = {
        .hci_family = AF_BLUETOOTH,
        .hci_dev = (uint16_t)interfaceId
    };
    
    // We first get the HCI socket on raw mode
    devDesc = socket(AF_BLUETOOTH, SOCK_RAW | SOCK_CLOEXEC, BTPROTO_HCI);

    if (devDesc < 0)
        return -1; // TODO, throw exception
    
    bzero(&devInfo, sizeof(devInfo));
    
    if (ioctl(devDesc, HCIGETDEVINFO, reinterpret_cast<void *>(&devInfo)) == -1)
        return -1;
    
    // We retrieve the address of the adapter
    address = devInfo.bdaddr;
    
    // Binding socket is important in order to be able to control our HCI socket
    if (bind(devDesc, (struct sockaddr *)&sockAddr, sizeof(sockAddr)) < 0)
        return -1; // TODO, throw exception
    return devDesc;
}

// TODO, must be implemented. Packet won't be "void *" type but something else
bool                                BluezHCI::sendRawPacket(int hciSocket, void *packet, uint8_t length)
{
    // TODO, implement
    (void)hciSocket;
    (void)packet;
    (void)length;
    return true;
}

/* ISubject */

void                                BluezHCI::attach(IObserver *observer)
{
    _observers.push_back(observer);
}

void                                BluezHCI::detach(IObserver *observer)
{
    _observers.remove(observer);
}

void                                BluezHCI::notifyAll()
{
    for (IObserver *observer : _observers)
        observer->update(this);
}

/* !ISubject */

BluezHCI::~BluezHCI()
{
    // TODO, implement
}

//
// PRIVATE
//

BluezHCI::BluezHCI() : ISubject()
{

} 

void                                BluezHCI::getPacket()
{
    // TODO, implement...
}

bool                                BluezHCI::getSinglePacket()
{
    // TODO, implement...
}