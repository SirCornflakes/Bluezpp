#include <unistd.h>

#include "Miscs/TraitsExtended.hpp"

#include "Adapter/Adapter.hpp"
#include "Adapter/AdapterTypeTraits.hpp"

//
// PUBLIC
//

inline int                      Adapter::getInterfaceId() const
{
    return _interface;
}

inline const BluetoothAddress   &Adapter::getAddress() const
{
    return _address;
}

inline AdapterRole              Adapter::getRole() const
{
    return _role;
}

inline int                      Adapter::getHciSocket() const
{
    return _hciSocket;
}

template<typename T>
bool                            Adapter::operator==(T t) const
{
    if constexpr(AdapterComparable<int, T>::value)
        return _interface == t;
    // Possible but not recommanded
    else if constexpr(AdapterComparable<BluetoothAddress, T>::value)
        return _address == t;
    else if constexpr(AdapterComparable<Adapter, T>::value)
        return _interface == t.getInterfaceId();
    else
        static_assert(AdapterComparableError<T>::value, AdapterInvalidComparison);
}

Adapter::~Adapter()
{
    close(_hciSocket);
}

//
// PRIVATE
//

Adapter::Adapter(int interface, const BluetoothAddress &address, int hciSocket) :
    _interface(interface), _address(address), _hciSocket(hciSocket)
{

}


inline Adapter                  &Adapter::setAddress(const BluetoothAddress &address)
{
    _address = address;
    return *this;
}

inline Adapter                  &Adapter::setRole(AdapterRole adapterRole)
{
    _role = adapterRole;
    return *this;
}

inline Adapter                  &Adapter::setState(AdapterState state)
{
    _state = state;
    return *this;
}