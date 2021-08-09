/**********************************************************************************
* 
* Bluez MGMT API
* 
* C++ Wrapper of the Bluez MGMT API.
* The Bluez MGMT API is used to manage the behavior of every Bluetooth adapters.
* For more information, visit
* 
* https://git.kernel.org/pub/scm/bluetooth/bluez.git/tree/doc/mgmt-api.txt
* 
/**********************************************************************************/

#pragma once

#include <atomic>
#include <memory>
#include <queue>
#include <list>
#include <mutex>
#include <cstdint>
#include <thread>

#include "Bluez/MGMT/MGMTCommand.hpp"
#include "Bluez/MGMT/MGMTEvent.hpp"

#include "Miscs/ISubject.hpp"

class BluezMGMT : public ISubject
{
    public:
        typedef std::queue<std::unique_ptr<MGMTEventPacket>> MGMTEventQueue;

        static BluezMGMT                    *Instance();

        std::unique_ptr<MGMTEventPacket>    getEvent();

        bool                                sendCommand(MGMTCommandPacket *packet, uint8_t length);

        void                                eventBlock(bool);

        bool                                createMGMTSocket();

        void                                closeMGMTSocket();

        bool                                isInitialized() const;

        bool                                isEventBlocking() const;

        /* ISubject */

        virtual void                        attach(IObserver *);

        virtual void                        detach(IObserver *);
        
        virtual void                        notifyAll();

        /* !ISubject */


        virtual                             ~BluezMGMT();

    private:
        explicit                            BluezMGMT();

        void                                getPacket();

        bool                                getSinglePacket();

        MGMTEventQueue                      _events;
        std::mutex                          _eventMutex;
        std::list<IObserver *>              _observers;
        std::atomic<bool>                   _eventBlock = false;
        std::thread                         _getPacketThread;
        int                                 _mgmtSocket = -1;
};