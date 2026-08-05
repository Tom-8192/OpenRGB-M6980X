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

/* Confirmed via ghost_interfaces.py:
   Interface 1, Col01, Usage Page 0xFF03 is the vendor control interface.
   This is MI_01&Col01 - the interface that accepts LED colour commands. */
#define GIGABYTE_GHOST_USAGE_PAGE  0xFF03

DetectedControllers DetectGigabyteGhostControllers(hid_device_info* info, const std::string& name)
{
    DetectedControllers detected_controllers;

    /* MI_00 (Interface 0, Usage Page 0x01) is the correct path.
       Confirmed: GHOST_Color_Tool.py uses hid.enumerate()[0] = MI_00.
       OpenRGB filters interface_number==0 before calling us. */
    hid_device* dev = hid_open_path(info->path);
    if(!dev)
    {
        return detected_controllers;
    }

    GigabyteGhostController*     controller     = new GigabyteGhostController(dev, *info, name);
    RGBController_GigabyteGhost* rgb_controller = new RGBController_GigabyteGhost(controller);
    detected_controllers.push_back(rgb_controller);

    return detected_controllers;
}

void RegisterGigabyteGhostDetector()
{
    /* Register for interface 0 (MI_00) - the path GHOST_Color_Tool.py uses.
       Python: hid.enumerate(VID, PID)[0] = MI_00, interface=0, usage_page=0x01 */
    DetectionManager::get()->RegisterHIDDeviceDetector("Gigabyte GHOST M6980X", DetectGigabyteGhostControllers, GIGABYTE_GHOST_VID, GIGABYTE_GHOST_PID, 0, HID_USAGE_PAGE_ANY, HID_USAGE_ANY);
}
