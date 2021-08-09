#pragma once
#include <type_traits>
#include <string_view>

#include "Miscs/TraitsExtended.hpp"

class BluetoothAddress;
class Adapter;

// String has to be literal in order to be used as second parameter of static_assert.
#define AdapterInvalidComparison "Invalid comparison. Make sure to compare either an int, an Address or an Adapter"

template<typename T, typename COMP>
struct AdapterComparable
{ 
    static const bool value = false;
};

template<typename T>
struct AdapterComparableError
{ 
    static const bool value = false;
};

// Compare Adapter with interfaceId
// This comparison only works if the interface Id > 0
template<typename COMP>
struct AdapterComparable<int, COMP>
{
    static const bool value = std::is_same<remove_cvref_t<COMP>, int>::value;
};

// Compare Adapter with another one.
// In reality, only interfaces are compared.
template<typename COMP>
struct AdapterComparable<BluetoothAddress, COMP>
{
    static const bool value = std::is_same<remove_cvref_t<COMP>, BluetoothAddress>::value;
};

// It is also possible to compare 2 addresses.
// This comaprison isn't recommanded even though
// in 90% of cases, addresses are unique.
template<typename COMP>
struct AdapterComparable<Adapter, COMP>
{
    static const bool value = std::is_same<remove_cvref_t<COMP>, Adapter>::value;
};