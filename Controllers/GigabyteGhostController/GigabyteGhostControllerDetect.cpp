/*---------------------------------------------------------*\
| GigabyteGhostControllerDetect.cpp                         |
|                                                           |
|   Detector for Gigabyte GHOST Gaming Mouse (M6980X)       |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/

#include "DetectionManager.h"
#include "hidapi.h"
#include "GigabyteGhostController.h"
#include "RGBController_GigabyteGhost.h"

DetectedControllers DetectGigabyteGhostControllers(hid_device_info* info, const std::string& name)
{
    DetectedControllers detected_controllers;

    /* GHOST_Color_Tool.py (confirmed working) uses hid.enumerate()[0] -
       the very first path, with NO interface_number filter.
       We do the same: accept the first call only, via static guard. */
    static bool registered = false;
    if(registered)
    {
        return detected_controllers;
    }

    hid_device* dev = hid_open_path(info->path);
    if(!dev)
    {
        return detected_controllers;
    }

    hid_set_nonblocking(dev, 1);

    GigabyteGhostController*     controller     = new GigabyteGhostController(dev, *info, name);
    RGBController_GigabyteGhost* rgb_controller = new RGBController_GigabyteGhost(controller);
    detected_controllers.push_back(rgb_controller);
    registered = true;

    return detected_controllers;
}

void RegisterGigabyteGhostDetector()
{
    DetectionManager::get()->RegisterHIDDeviceDetector("Gigabyte GHOST M6980X", DetectGigabyteGhostControllers, GIGABYTE_GHOST_VID, GIGABYTE_GHOST_PID, 1, HID_USAGE_PAGE_ANY, HID_USAGE_ANY);
}
