#pragma once

#include <string_view>
#include <type_traits>

#include <bluetooth/bluetooth.h>

#include "Miscs/TraitsExtended.hpp"

// String has to be literal in order to be used as second parameter of static_assert.
#define BluetoothAddressInvalidType "Invalid BluetoothAddress Type. Must be a string, an interger or a char pointer."

template<typename T, typename COMP>
struct BluetoothAddressValid
{
    static const bool value = false;
};

template<typename T>
struct BluetoothAddressInvalid
{
    static const bool value = false;
};

template<typename CMP>
struct BluetoothAddressValid<uint64_t, CMP>
{
    static const bool value = std::is_same<remove_cvref_t<CMP>, uint64_t>::value;
};

template<typename CMP>
struct BluetoothAddressValid<uint8_t *, CMP>
{
    static const bool value = std::is_same<remove_cvref_t<CMP>, uint8_t *>::value;
};

template<typename CMP>
struct BluetoothAddressValid<uint8_t[6], CMP>
{
    static const bool value = std::is_same<remove_cvref_t<CMP>, uint8_t[6]>::value;
};

template<typename CMP>
struct BluetoothAddressValid<std::string, CMP>
{
    static const bool value = std::is_same<remove_cvref_t<CMP>, std::string>::value;
};

