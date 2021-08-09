# Bluezpp

Bluezpp is a library made to manage all bluetooth adapters on any Linux devices in C++ 17. It allows the user to scan, advertise and connect to a BLE or BR/EDR device .


Bluezpp uses the [MGMT API](https://git.kernel.org/pub/scm/bluetooth/bluez.git/tree/doc/mgmt-api.txt)
and the raw socket from Bluez. If you want more information about Bluetooth BREDR or LE, I strongly recommand to read
the [Bluetooth Core Specification](https://www.bluetooth.org/DocMan/handlers/DownloadDoc.ashx?doc_id=286439).


# How does it work ?

The library is in progress...


## Configuration

First thing first, you need to configure the adapter you want to work with.

```cpp
#include "Adapter/AdapterManager.hpp"

int main(int argc, char **argv)
{
    // You can find your interface number by executing the hciconfig command on your shell
    Adapter *adapter = AdapterManager.Instance().getAdapter(0);

    ...

    // In progress ...

    for (;;) {}

    return 0;
}
```

# What should be implemented

- Configuration of the adapter (BR/EDR mode, advertising data, scanning data through HCI socket or MGMT socket)
- Add more profiles (ATT, HIDP, SDP, RFCOMM)
- Configuration of profiles
- Callback to catch all events (New connection, Disconnection, Pairing, Powered, Off, Error)

# How to build

The library use a cmake 2.8 as minimum version number. The library is quite easy to build.

While using it, make sure all Bluez services are off in order to avoid conflict between your program and Bluez services.

