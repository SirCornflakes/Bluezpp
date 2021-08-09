#pragma once

#include <cstdint>

#include "Bluez/MGMT/MGMTCommandComplete.hpp"


struct __attribute__((packed)) MGMTCommandStatus : public MGMTCommandComplete
{
    MGMTCommandStatus() : code(0x002) {}
};