/**********************************************************************************
* 
* Bluez MGMT API
* 
* C++ Wrapper of the Bluez MGMT API.
* The Bluez MGMT API is used to manage the behavior of the adapter.
* For more information, visit
* 
* https://git.kernel.org/pub/scm/bluetooth/bluez.git/tree/doc/mgmt-api.txt
* 
/**********************************************************************************/

#pragma once

#include <cstdint>

struct __attribute__((packed)) CommandComplete
{
    uint16_t code = 0x0001;
    uint16_t controller;
    uint16_t length;
    uint16_t opcode;
    MGMTError status;
};