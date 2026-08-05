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
    static bool detected = false;

    if(detected)
    {
        return detected_controllers;
    }

    if(info->interface_number == 1 || info->interface_number == -1)
    {
        hid_device* dev = hid_open_path(info->path);

        if(dev)
        {
            GigabyteGhostController*     controller     = new GigabyteGhostController(dev, *info, name);
            RGBController_GigabyteGhost* rgb_controller = new RGBController_GigabyteGhost(controller);

            detected_controllers.push_back(rgb_controller);
            detected = true;
        }
    }

    return detected_controllers;
}

void RegisterGigabyteGhostDetector()
{
    DetectionManager::get()->RegisterHIDDeviceDetector("Gigabyte GHOST M6980X", DetectGigabyteGhostControllers, GIGABYTE_GHOST_VID, GIGABYTE_GHOST_PID, 1, HID_USAGE_PAGE_ANY, HID_USAGE_ANY);
}
