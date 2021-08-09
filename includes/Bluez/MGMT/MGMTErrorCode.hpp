/**********************************************************************************
* 
* MGMT Event
* 
* Enum of all existing error code given by the Bluez MGMT API
* 
* For more information, visit
* 
* https://git.kernel.org/pub/scm/bluetooth/bluez.git/tree/doc/mgmt-api.txt
* 
/**********************************************************************************/

#pragma once

enum MGMTErrorCode
{
    Success = 0x00,
    UnknownCommand = 0x01,
    NotConnected = 0x02,
    Failed = 0x03,
    ConnectFailed = 0x04,
    AuthenticationFailed = 0x05,
    NotPaired = 0x06,
    NoResources = 0x07,
    Timeout = 0x08,
    AlreadyConnected = 0x09,
    Busy = 0x0A,
    Rejected = 0x0B,
    NotSupported = 0x0C,
    InvalidParameters = 0x0D,
    Disconnected = 0x0E,
    NotPowered = 0x0F,
    Cancelled = 0x10,
    InvalidIndex = 0x11,
    RFKilled = 0x12,
    AlreadyPaired = 0x13,
    PermissionDenied = 0x14
};