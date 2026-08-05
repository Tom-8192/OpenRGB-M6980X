/*---------------------------------------------------------*\
| RGBController_GigabyteGhost.cpp                           |
|                                                           |
|   OpenRGB driver interface for Gigabyte GHOST Mouse       |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/

#include "RGBController_GigabyteGhost.h"

static unsigned char QuantizeChannel(RGBColor channel_val)
{
    if(channel_val < 64)
    {
        return 0x00;
    }
    else if(channel_val < 192)
    {
        return 0x01;
    }
    return 0x02;
}

RGBController_GigabyteGhost::RGBController_GigabyteGhost(GigabyteGhostController* controller_ptr)
{
    controller  = controller_ptr;

    name        = controller->GetNameString();
    type        = DEVICE_TYPE_MOUSE;
    description = "Gigabyte GHOST Gaming Mouse Device";
    location    = controller->GetDeviceLocation();

    mode StaticMode;
    StaticMode.name       = "Static";
    StaticMode.value      = 0;
    StaticMode.flags      = MODE_FLAG_HAS_MODE_SPECIFIC_COLOR | MODE_FLAG_MANUAL_SAVE;
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

    unsigned char r = QuantizeChannel(RGBGetRValue(color));
    unsigned char g = QuantizeChannel(RGBGetGValue(color));
    unsigned char b = QuantizeChannel(RGBGetBValue(color));

    // Profile 0 (Profile 1 on mouse hardware)
    controller->SetProfileColor(0x00, r, g, b);
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
