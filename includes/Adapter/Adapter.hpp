/**********************************************************************************
* 
* Adapter
* 
* Adapter is the class that abstract the concept of
* Bluetooth interface
* 
* For example: HCI0, HCI1... (cf: man hciconfig(8))
* 
/**********************************************************************************/

#pragma once

#include "Adapter/BluetoothAddress.hpp"

//
// Forward declaration
//

class AdapterManager;

// When an Adapter is paired to a device,
// this one can be either a Master or a Slave
enum class AdapterRole
{
    RoleMaster = 0,
    RoleSlave
};

// Current state of the adapter
enum class AdapterState
{
    StateOff = 0,
    StateOn,
    StatePaired,
    StateConnected
};

class Adapter
{
    public:

        static constexpr int    NO_INTERFACE = -1;

        int                     getInterfaceId() const;

        const BluetoothAddress  &getAddress() const;

        AdapterRole             getRole() const;

        int                     getHciSocket() const;

        template<typename T>
        bool                operator==(T t) const;

        ~Adapter();
    private:
        friend class        AdapterManager;

        Adapter(int interface, const BluetoothAddress &, int hciSocket);
        
        Adapter(const Adapter &) = delete;

        Adapter             &setAddress(const BluetoothAddress &);

        Adapter             &setRole(AdapterRole);

        Adapter             &setState(AdapterState);


        const int           _interface;
        BluetoothAddress    _address;
        int                 _hciSocket;
        AdapterRole         _role = AdapterRole::RoleMaster;
        AdapterState        _state = AdapterState::StateOff;
};