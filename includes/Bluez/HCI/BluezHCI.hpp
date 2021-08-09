/**********************************************************************************
* 
* Bluez HCI API
* 
* C++ Wrapper of the HCI API.
* The Bluez HCI API is used to manage the behavior of every Bluetooth adapters by
* controlling the HCI layer which is the lowest layer. 
* 
* For more information, read Bluetooth Core Specification 4.X or 5.X
* 
/**********************************************************************************/

#pragma once

#include <thread>

#include "Adapter/BluetoothAddress.hpp"

#include "Miscs/ISubject.hpp"

// TODO, create an interface for BluezHCI and BluezMGMT called "BluezAPI"

class BluezHCI : public ISubject
{
    public:
        static BluezHCI                     *Instance();

        void                                *getHCIPacket();

        int                                 getBluetoothAddressBy(int interfaceId, BluetoothAddress &address) const;

        bool                                sendRawPacket(int hci_socket, void *packet, uint8_t length);

        /* ISubject */

        virtual void                        attach(IObserver *);

        virtual void                        detach(IObserver *);
        
        virtual void                        notifyAll();

        /* !ISubject */

        virtual                             ~BluezHCI();

    private:
        explicit                            BluezHCI();

        void                                getPacket();

        bool                                getSinglePacket();

        std::thread                         _getPacketThread;
        std::list<IObserver *>              _observers;
};