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

/* Single shared controller instance - all HID paths for this device are
   added to it so colour packets are broadcast to every interface,
   which matches the behaviour (and colour control) seen when all 3
   collections were registered as separate devices. */
static GigabyteGhostController* g_ghost_controller = nullptr;

DetectedControllers DetectGigabyteGhostControllers(hid_device_info* info, const std::string& name)
{
    DetectedControllers detected_controllers;

    /* Interface 0 is the correct control interface for this device.
       Confirmed via ghost_static.py reverse engineering. */
    if(info->interface_number != 0)
    {
        return detected_controllers;
    }

    hid_device* dev = hid_open_path(info->path);
    if(!dev)
    {
        return detected_controllers;
    }

    /* Non-blocking mode - required for reliable HID communication */
    hid_set_nonblocking(dev, 1);

    GigabyteGhostController*     controller     = new GigabyteGhostController(dev, *info, name);
    RGBController_GigabyteGhost* rgb_controller = new RGBController_GigabyteGhost(controller);
    detected_controllers.push_back(rgb_controller);

    return detected_controllers;
}

void RegisterGigabyteGhostDetector()
{
    DetectionManager::get()->RegisterHIDDeviceDetector("Gigabyte GHOST M6980X", DetectGigabyteGhostControllers, GIGABYTE_GHOST_VID, GIGABYTE_GHOST_PID, 1, HID_USAGE_PAGE_ANY, HID_USAGE_ANY);
}
