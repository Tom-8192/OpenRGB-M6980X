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

    std::string GetDeviceLocation();
    std::string GetFirmwareVersion();
    std::string GetNameString();
    std::string GetSerialString();

    void        UnlockDevice();
    void        SetProfileColor(unsigned char profile, unsigned char r, unsigned char g, unsigned char b);

private:
    hid_device* dev;
    std::string location;
    std::string name;
    std::string version;

    void        Flush();
    void        SendFeatureReport(const unsigned char* data, size_t size);
};
