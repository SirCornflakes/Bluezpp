// memcmp
#include <cstring>

#include "Adapter/BluetoothAddress.hpp"
#include "Miscs/TraitsExtended.hpp"
#include "Adapter/BluetoothAddressTypeTrait.hpp"

//
//  PUBLIC
//

BluetoothAddress::BluetoothAddress() {}

BluetoothAddress::BluetoothAddress(const bdaddr_t &bdAddress)
{
    memcmp(_binAddr.addrByte, &bdAddress, ADDRESS_SIZE);
}

BluetoothAddress::BluetoothAddress(const std::string &strAddress)
{
    convert(strAddress);
}

BluetoothAddress::BluetoothAddress(uint64_t intAddr)
{
    _binAddr.addrInt = intAddr;
}

BluetoothAddress::BluetoothAddress(uint8_t *byteAddr)
{
    for (int index = 0; index < ADDRESS_SIZE; ++index)
        _binAddr.addrByte[index] = byteAddr[index];
}

BluetoothAddress::BluetoothAddress(const BluetoothAddress &address)
{
    _binAddr.addrInt = address.getAddress<uint64_t>();
}

bool        BluetoothAddress::convert(const std::string &strAddress)
{
    uint64_t addrInt = 0;
        
    if (!addressIsValid(strAddress))
        return false;
    for (size_t index = 0; index < ADDRESS_SIZE; ++index)
    {
        std::string &&part = std::string(strAddress, (2 + (index * 3)));
        _binAddr.addrByte[ADDRESS_SIZE - index - 1] = std::stoi(part, 0, 16);
    }
    return true;
}

template<typename T>
T           BluetoothAddress::getAddress() const
{
    if constexpr(BluetoothAddressValid<uint64_t, T>::value)
        return _binAddr.addrInt;
    else if constexpr(BluetoothAddressValid<uint8_t *, T>::value || BluetoothAddressValid<uint8_t[6], T>::value)
        return _binAddr.addrByte;
    else if constexpr(BluetoothAddressValid<std::string, T>::value)
        return toString();
    else
        static_assert(BluetoothAddressInvalid<T>::value, BluetoothAddressInvalidType);
}

template<typename T>
bool        BluetoothAddress::operator==(T t) const
{
    if constexpr(BluetoothAddressValid<uint64_t, T>::value)
        return _binAddr.addrInt == t;
    else if constexpr(BluetoothAddressValid<uint8_t *, T>::value ||
                        BluetoothAddressValid<uint8_t[6], T>::value)
        return !memcmp(_binAddr.addrByte, t, ADDRESS_SIZE);
    else if constexpr(BluetoothAddressValid<std::string, T>::value)
        return toString() == t;
    else
        static_assert(BluetoothAddressInvalid<T>::value, BluetoothAddressInvalidType);
}

//
// PRIVATE
//

bool        BluetoothAddress::addressIsValid(const std::string &addr) const
{
    return std::regex_match(addr, ADDRESS_REGEX);
}