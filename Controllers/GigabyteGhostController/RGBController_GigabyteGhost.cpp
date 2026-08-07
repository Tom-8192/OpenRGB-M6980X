/*---------------------------------------------------------*\
| RGBController_GigabyteGhost.cpp                           |
|                                                           |
|   OpenRGB driver interface for Gigabyte GHOST Mouse       |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/

#include "RGBController_GigabyteGhost.h"

/**------------------------------------------------------------------*\
    @name Gigabyte GHOST Gaming Mouse (M6980X)
    @category Mouse
    @type USB
    @save :x:
    @direct :white_check_mark:
    @effects :x:
    @detectors DetectGigabyteGhostControllers
    @comment
\*-------------------------------------------------------------------*/

RGBController_GigabyteGhost::RGBController_GigabyteGhost(GigabyteGhostController* controller_ptr)
{
    controller  = controller_ptr;

    name        = controller->GetNameString();
    type        = DEVICE_TYPE_MOUSE;
    description = "Gigabyte GHOST Gaming Mouse Device";
    location    = controller->GetDeviceLocation();

    mode StaticMode;
    StaticMode.name       = "Direct";
    StaticMode.value      = 0;
    StaticMode.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    StaticMode.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(StaticMode);

    SetupZones();
}

RGBController_GigabyteGhost::~RGBController_GigabyteGhost()
{
    delete controller;
}

void RGBController_GigabyteGhost::SetupZones()
{
    zone profile_zone;
    profile_zone.name       = "Hardware Profiles";
    profile_zone.type       = ZONE_TYPE_LINEAR;
    profile_zone.leds_min   = 3;
    profile_zone.leds_max   = 3;
    profile_zone.leds_count = 3;
    profile_zone.matrix_map = NULL;
    zones.push_back(profile_zone);

    led p1_led;
    p1_led.name = "Profile 1 Color";
    leds.push_back(p1_led);

    led p2_led;
    p2_led.name = "Profile 2 Color";
    leds.push_back(p2_led);

    led p3_led;
    p3_led.name = "Profile 3 Color";
    leds.push_back(p3_led);

    SetupColors();
}

void RGBController_GigabyteGhost::ResizeZone(int /*zone*/, int /*new_size*/)
{
}

void RGBController_GigabyteGhost::DeviceUpdateLEDs()
{
    if(colors.size() < 3)
    {
        return;
    }

    unsigned char r[3];
    unsigned char g[3];
    unsigned char b[3];

    for(int i = 0; i < 3; i++)
    {
        r[i] = RGBGetRValue(colors[i]);
        g[i] = RGBGetGValue(colors[i]);
        b[i] = RGBGetBValue(colors[i]);
    }

    controller->SetAllProfileColors(r, g, b);
}

void RGBController_GigabyteGhost::UpdateZoneLEDs(int /*zone*/)
{
    DeviceUpdateLEDs();
}

void RGBController_GigabyteGhost::UpdateSingleLED(int /*led*/)
{
    DeviceUpdateLEDs();
}

void RGBController_GigabyteGhost::DeviceUpdateMode()
{
    DeviceUpdateLEDs();
}
