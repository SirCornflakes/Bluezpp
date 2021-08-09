#include <type_traits>
#include "Adapter/AdapterManager.hpp"
#include "Bluez/MGMT/BluezMGMT.hpp"
#include "Bluez/HCI/BluezHCI.hpp"

//
// PUBLIC
//


/* AObserver */

void                        AdapterManager::update(ISubject *value)
{
    if (value == BluezMGMT::Instance())
        getBluezMGMTPacket();
    // TODO, implement bluez raw socket
    else if (value == BluezHCI::Instance())
        getBluezHCIPacket();
}

/* !AObserver */

// Singleton, can be instanciate only once.
AdapterManager              &AdapterManager::Instance()
{
    static AdapterManager am;

    return am;
}

// The attribute here should be either:
// - int: refers to the adapter interface id
// - BluetoothAddress: Address of the device. It's not recommanded to 
//               get an adapter by its address even though 90% of
//               the cases, addresses are uniques.
template<typename T>
const Adapter               *AdapterManager::getAdapter(T att) const
{
    for (const auto & adapterPair : _adapterPairsList)
    {
        if (adapterPair.first == att)
            return &adapterPair.first;
    }
    return nullptr;
}

AdapterManager::~AdapterManager()
{
    BluezMGMT::Instance()->detach(this);
    BluezHCI::Instance()->detach(this);
}

//
// PRIVATE
//

void                        AdapterManager::getBluezMGMTPacket()
{
    BluezMGMT *bmgmt = BluezMGMT::Instance();
    std::unique_ptr<MGMTEventPacket> eventPacket = std::move(bmgmt->getEvent());

    (void)eventPacket;
    // TODO, implement...
}

void                        AdapterManager::getBluezHCIPacket()
{
    BluezMGMT               *bluezHCI = BluezMGMT::Instance();

    (void)bluezHCI;
    // Todo, implement...
}

void                        AdapterManager::getAllAdapters()
{
    int                     hciSocket;
    BluetoothAddress        address;
    BluezHCI                *bluezHCI = BluezHCI::Instance();

    for (int interfaceNumber = 0; interfaceNumber < AdapterManager::maxAdapterNumber; ++interfaceNumber)
    {
        hciSocket = bluezHCI->getBluetoothAddressBy(interfaceNumber, address);
        if (hciSocket >= 0)
        {
            Adapter *adapter = new Adapter(interfaceNumber, address, hciSocket);
            // The second parameter is nullptr because the adapter isn't paired with anyone
            _adapterPairsList.push_back(std::make_pair(adapter, nullptr));
        }
    }
}

AdapterManager::AdapterManager() : IObserver()
{
    BluezMGMT::Instance()->attach(this);
    BluezHCI::Instance()->attach(this);
}