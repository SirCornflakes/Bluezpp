/**********************************************************************************
* 
* MGMT Event
* 
* Every MGMT Command has as reply a MGMT Event
* 
* For more information, visit
* 
* https://git.kernel.org/pub/scm/bluetooth/bluez.git/tree/doc/mgmt-api.txt
* 
/**********************************************************************************/

#pragma once

#include <cstdint>
#include <cstring>
#include <limits>

#include "MGMTErrorCode.hpp"

enum class                      MGMTEventCode : uint16_t
{
    MGMTEventUndefined = 0x00,
    MGMTEventCommandeComplete,
    MGMTEventCommandeStatus,
    MGMTEventControllerError,
    MGMTEventIndexAdded,
    MGMTEventIndexRemoved,
    MGMTEventNewSettings,
    MGMTEventClassOfDeviceChanged,
    MGMTEventLocalNameChanged,
    MGMTEventNewLinkKey,
    MGMTEventNewLongTermKey,
    MGMTEventDeviceConnected,
    MGMTEventDeviceDisconnected,
    MGMTEventConnectFailed,
    MGMTEventPINCodeRequest,
    MGMTEventUserConfirmationRequest,
    MGMTEventUserPasskeyRequest,
    MGMTEventAuthenticationFailed,
    MGMTEventDeviceFound,
    MGMTEventDiscovering,
    MGMTEventDeviceBlocked,
    MGMTEventDeviceUnblocked,
    MGMTEventDeviceUnpaired,
    MGMTEventPasskeyNotify,
    MGMTEventNewIdentityResolvingKey,
    MGMTEventNewSignatureResolvingKey,
    MGMTEventDeviceAdded,
    MGMTEventDeviceRemoved,
    MGMTEventNewConnectionParameter,
    MGMTEventUnconfiguredIndexAdded,
    MGMTEventUnconfiguredIndexRemoved,
    MGMTEventNewConfigurationOptions,
    MGMTEventExtendedIndexAdded,
    MGMTEventExtendedIndexRemoved,
    MGMTEventLocalOutOfBandExtendedDataUpdated,
    MGMTEventAdvertisingAdded,
    MGMTEventAdvertisingRemoved,
    MGMTEventExtendedControllerInformationChanged,
};

typedef std::numeric_limits<char> charLimits;

typedef std::array<uint8_t, charLimits::max()> EventPacketByteArray;

struct __attribute__((packed)) MGMTEventHeader
{
    MGMTEventHeader(const MGMTEventCode evCode) :
        eventCode(evCode) {}

    void                        operator=(const MGMTEventCode evCode)
    {
        eventCode = evCode;
    }

    MGMTEventCode               eventCode;
    uint16_t                    controllerIndex;
    uint16_t                    parameterLength;
};

struct __attribute__((packed)) MGMTEventPacket 
{
    MGMTEventHeader             header = MGMTEventCode::MGMTEventUndefined;
    uint8_t                     data[charLimits::max()];
    void                        operator=(const EventPacketByteArray &evba)
    {
        memcpy(this, evba.data(), sizeof(MGMTEventPacket));
    }
};

struct __attribute__((packed))  MGMTEventCommandCompletePacket
{
    MGMTEventHeader             header = MGMTEventCode::MGMTEventCommandeComplete;
    uint16_t                    opcode;
    MGMTErrorCode               status;
    uint8_t                     returnParameters[charLimits::max()];
};

struct __attribute__((packed))  MGMTEventCommandStatusPacket
{
    MGMTEventHeader             header = MGMTEventCode::MGMTEventCommandeStatus;
    uint16_t                    opcode;
    MGMTErrorCode               status;
};

// TODO, implement all events.