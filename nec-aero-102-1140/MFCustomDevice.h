#pragma once

#include <Arduino.h>
#include "nec-aero-102-1140.h"

class MFCustomDevice
{
public:
    MFCustomDevice();
    void attach(uint16_t adrPin, uint16_t adrType, uint16_t adrConfig);
    void detach();
    void update();
    void set(int16_t messageID, char *setPoint);

private:
    bool           _initialized = false;
    NecAeroScreen *_mydevice;
    uint8_t        _customType = 0;
};
