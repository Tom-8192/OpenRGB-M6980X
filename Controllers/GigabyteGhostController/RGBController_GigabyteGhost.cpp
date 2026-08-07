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

    mode Profile1;
    Profile1.name       = "Profile 1";
    Profile1.value      = 0;
    Profile1.flags      = MODE_FLAG_HAS_MODE_SPECIFIC_COLOR | MODE_FLAG_MANUAL_SAVE;
    Profile1.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Profile1);

    mode Profile2;
    Profile2.name       = "Profile 2";
    Profile2.value      = 1;
    Profile2.flags      = MODE_FLAG_HAS_MODE_SPECIFIC_COLOR | MODE_FLAG_MANUAL_SAVE;
    Profile2.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Profile2);

    mode Profile3;
    Profile3.name       = "Profile 3";
    Profile3.value      = 2;
    Profile3.flags      = MODE_FLAG_HAS_MODE_SPECIFIC_COLOR | MODE_FLAG_MANUAL_SAVE;
    Profile3.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Profile3);

    SetupZones();
}

RGBController_GigabyteGhost::~RGBController_GigabyteGhost()
{
    delete controller;
}

void RGBController_GigabyteGhost::SetupZones()
{
    zone logo_zone;
    logo_zone.name       = "Logo LED";
    logo_zone.type       = ZONE_TYPE_SINGLE;
    logo_zone.leds_min   = 1;
    logo_zone.leds_max   = 1;
    logo_zone.leds_count = 1;
    zones.push_back(logo_zone);

    led logo_led;
    logo_led.name = "Logo LED";
    leds.push_back(logo_led);

    SetupColors();
}

void RGBController_GigabyteGhost::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /* Single LED zone cannot be resized */
}

void RGBController_GigabyteGhost::DeviceUpdateLEDs()
{
    if(colors.empty())
    {
        return;
    }

    RGBColor color = colors[0];

    unsigned char r = RGBGetRValue(color);
    unsigned char g = RGBGetGValue(color);
    unsigned char b = RGBGetBValue(color);

    unsigned char current_profile = modes[active_mode].value;

    controller->SetProfileColor(current_profile, r, g, b);
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
