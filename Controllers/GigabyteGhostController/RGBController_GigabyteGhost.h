/*---------------------------------------------------------*\
| RGBController_GigabyteGhost.h                             |
|                                                           |
|   OpenRGB driver interface for Gigabyte GHOST Mouse       |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/

#pragma once

#include "RGBController.h"
#include "GigabyteGhostController.h"

class RGBController_GigabyteGhost : public RGBController
{
public:
    RGBController_GigabyteGhost(GigabyteGhostController* controller_ptr);
    ~RGBController_GigabyteGhost();

    void        SetupZones();
    void        ResizeZone(int zone, int new_size);
    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        DeviceUpdateMode();

private:
    GigabyteGhostController* controller;
};
