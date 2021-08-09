#include <unistd.h>
#include <utility>
#include <poll.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>

#include "Bluez/MGMT/BluezMGMT.hpp"

//
// PUBLIC
//


// Having more than one instance of BluezMGMT could cause undefined behaviors
BluezMGMT                           *BluezMGMT::Instance()
{
    static BluezMGMT                instance;

    return &instance;       
}


std::unique_ptr<MGMTEventPacket>    BluezMGMT::getEvent()
{
    std::scoped_lock                eventLock(_eventMutex);
    std::unique_ptr                 mgmtEv = std::move(_events.front());

    _events.pop();
    return mgmtEv;
}

bool                                BluezMGMT::sendCommand(MGMTCommandPacket *packet, uint8_t packetLength)
{
    bool                            isSent = false;

    isSent = (_mgmtSocket > 0) &&
                (write(_mgmtSocket, static_cast<void *>(packet), packetLength) > 0);
    if (!isSent)
        return false;
    // If blocking mode is chosen, retrieve the event right after sending the command.
    if (isEventBlocking())
        return getSinglePacket();
    return true;
}


// It's possible to choose if after sending a command
// the sendCommand should block until an event is received.
inline void                         BluezMGMT::eventBlock(bool block)
{ 
    _eventBlock = block;
    if (!isEventBlocking() && !_getPacketThread.joinable())
        _getPacketThread = std::thread(&BluezMGMT::getPacket, this);
}

bool                                BluezMGMT::createMGMTSocket()
{
    struct sockaddr_hci             addr;
    struct sockaddr                 sockad;

    _mgmtSocket = socket(PF_BLUETOOTH, SOCK_RAW | SOCK_CLOEXEC,
                            BTPROTO_HCI);

    if (_mgmtSocket < 0)
        return false; // TODO, add exceptions when the MGMT socket is unavailable.

    memset(&addr, 0, sizeof(struct sockaddr_hci));
    memset(&sockad, 0, sizeof(struct sockaddr));
    addr.hci_family = AF_BLUETOOTH;
    addr.hci_dev = HCI_DEV_NONE;
    addr.hci_channel = HCI_CHANNEL_CONTROL;

    memcpy(&sockad, &addr, sizeof(struct sockaddr_hci));
    if (bind(_mgmtSocket, &sockad, sizeof(struct sockaddr)) < 0)
    {
        close(_mgmtSocket);
        _mgmtSocket = -1;
        return false; // TODO, add exceptions when the MGMT socket is unavailable.
    }
    if (!isEventBlocking() && !_getPacketThread.joinable())
        _getPacketThread = std::thread(&BluezMGMT::getPacket, this);
    return true;
}

void                                BluezMGMT::closeMGMTSocket()
{
    close(_mgmtSocket);
    _mgmtSocket = -1;
}

inline bool                         BluezMGMT::isEventBlocking() const { return _eventBlock; }

inline bool                         BluezMGMT::isInitialized() const { return _mgmtSocket; }

/* ISubject */

void                                BluezMGMT::attach(IObserver *obs)
{
    _observers.push_back(obs);
}

void                                BluezMGMT::detach(IObserver *obs)
{
    _observers.remove(obs);
}

void                                BluezMGMT::notifyAll()
{
    for (IObserver *observer : _observers)
        observer->update(this);
}

/* !ISubject */


BluezMGMT::~BluezMGMT()
{
    closeMGMTSocket();
    // Waiting for the thread to be joinable before destoying the instance.
    while (_getPacketThread.joinable());
}

//
// PRIVATE
//

bool                                BluezMGMT::getSinglePacket()
{
    struct pollfd                   fds[1] = {
        {.fd = _mgmtSocket,
            .events = POLLIN}
    };

    if (!isInitialized())
        return false;
    // TODO, throw an exception when it fails.
    if (poll(fds, 1, 1000) < 0)
    {
        _mgmtSocket = -1;
        return false;
    }
    if (fds[0].revents & POLLIN)
    {
        std::scoped_lock                    eventLock(_eventMutex);
        EventPacketByteArray                packet;
        uint8_t                             packetLength;
        std::unique_ptr<MGMTEventPacket>    eventPacket(new MGMTEventPacket);

        packetLength = read(_mgmtSocket, packet.data(), packet.size());
        *eventPacket = packet;
        _events.push(std::move(eventPacket));
    }
    return true;
}

// Async function. It calls notifyAll everytime a new packet is fetched.
void                                BluezMGMT::getPacket()
{
    while (isInitialized() && !isEventBlocking())
    {
        if (getSinglePacket())
            notifyAll();
    }
    _getPacketThread.join();
}

BluezMGMT::BluezMGMT() : ISubject()
{
}