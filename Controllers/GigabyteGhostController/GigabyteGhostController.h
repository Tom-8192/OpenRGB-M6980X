/*---------------------------------------------------------*\
| GigabyteGhostController.h                                 |
|                                                           |
|   Driver for Gigabyte GHOST Gaming Mouse (M6980X)         |
|                                                           |
|   Reverse Engineering & Protocol: GHOST Reverse Eng. Team |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/

#pragma once

#include <string>
#include <vector>
#include <hidapi.h>
#include "RGBController.h"

#define GIGABYTE_GHOST_VID                  0xE0FF
#define GIGABYTE_GHOST_PID                  0x0001
#define GIGABYTE_GHOST_REPORT_SIZE          9

class GigabyteGhostController
{
public:
    GigabyteGhostController(hid_device* dev_handle, const hid_device_info& info, std::string dev_name);
    ~GigabyteGhostController();

    /* Add an additional HID path for the same physical device.
       Colour commands will be broadcast to all open handles. */
    void        AddDevice(hid_device* extra_handle);

    std::string GetDeviceLocation();
    std::string GetFirmwareVersion();
    std::string GetNameString();
    std::string GetSerialString();

    void        SetProfileColor(unsigned char profile, unsigned char r, unsigned char g, unsigned char b);

private:
    std::vector<hid_device*> devs;   /* all open HID handles for this mouse */
    std::string              location;
    std::string              name;
    std::string              version;

    void        SendFeatureReportAll(const unsigned char* data, size_t size);
    void        UnlockDevice(hid_device* dev);
};
