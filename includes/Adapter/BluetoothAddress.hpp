/**********************************************************************************
* 
* Bluetooth Address
* 
* 
* Simple wrapper for braddr Address
* 
/**********************************************************************************/

#pragma once

#include <string>
#include <memory>
#include <cstdint>
#include <regex>

#include <bluetooth/bluetooth.h>

class BluetoothAddress
{
    public: 
        static constexpr std::string_view   ADDRESS_ANY = "00:00:00:00:00:00";
        static constexpr size_t             ADDRESS_SIZE = 6;
        static inline std::regex            ADDRESS_REGEX{"^([a-fA-F0-9]{2}:){5}([a-fA-F0-9]{2})$"};

        BluetoothAddress();

        BluetoothAddress(const bdaddr_t &);

        BluetoothAddress(const std::string &);

        BluetoothAddress(uint64_t intAddr);
        
        BluetoothAddress(uint8_t *byteAddr);

        BluetoothAddress(const BluetoothAddress &);

        std::string     toString() const;

        template<typename T>
        T               getAddress() const;

        template<typename T>
        bool            operator==(T t) const;

        bool            convert(const std::string &);

    private:
        bool  addressIsValid(const std::string &addr) const;
        
        union BinaryAddress {
            uint64_t addrInt;
            uint8_t  addrByte[6];
        };

        BinaryAddress _binAddr = {
            .addrInt = 0
        };
};