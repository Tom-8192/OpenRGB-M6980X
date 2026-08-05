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
#include <mutex>
#include <hidapi.h>
#include "RGBController.h"

#define GIGABYTE_GHOST_VID                  0xE0FF
#define GIGABYTE_GHOST_PID                  0x0001
#define GIGABYTE_GHOST_REPORT_SIZE          9

class GigabyteGhostController
{
public:
    GigabyteGhostController(hid_device* initial_dev, const hid_device_info& info, std::string dev_name);
    ~GigabyteGhostController();

    std::string GetDeviceLocation();
    std::string GetFirmwareVersion();
    std::string GetNameString();
    std::string GetSerialString();

    /* Opens a fresh HID handle, sends colour command, closes handle.
       Exactly mirrors GHOST_Color_Tool.py which always opens fresh. */
    void        SetProfileColor(unsigned char profile, unsigned char r, unsigned char g, unsigned char b);

private:
    std::string hid_path;   /* stored path to reopen per update */
    std::string location;
    std::string name;
    std::string version;
    std::mutex  update_mutex;

    static void Flush(hid_device* dev);
    static bool SendFeatureReport(hid_device* dev, const unsigned char* data, size_t size);
    static void UnlockDevice(hid_device* dev);
};
