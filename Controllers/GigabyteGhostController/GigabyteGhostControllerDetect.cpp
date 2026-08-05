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

    hid_device* dev = hid_open_path(info->path);
    if(!dev)
    {
        return detected_controllers;
    }

    if(g_ghost_controller == nullptr)
    {
        /* First interface: create the controller and expose it to OpenRGB */
        g_ghost_controller = new GigabyteGhostController(dev, *info, name);
        RGBController_GigabyteGhost* rgb_controller = new RGBController_GigabyteGhost(g_ghost_controller);
        detected_controllers.push_back(rgb_controller);
    }
    else
    {
        /* Additional interfaces: silently attach to the same controller */
        g_ghost_controller->AddDevice(dev);
    }

    return detected_controllers;
}

void RegisterGigabyteGhostDetector()
{
    DetectionManager::get()->RegisterHIDDeviceDetector("Gigabyte GHOST M6980X", DetectGigabyteGhostControllers, GIGABYTE_GHOST_VID, GIGABYTE_GHOST_PID, 1, HID_USAGE_PAGE_ANY, HID_USAGE_ANY);
}
