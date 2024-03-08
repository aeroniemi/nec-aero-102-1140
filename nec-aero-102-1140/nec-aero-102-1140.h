#pragma once

#include <Arduino.h>
#include "nec-aero-102-1140_screen.h"


class NecAeroScreen
{
public:
    NecAeroScreen();
    void attach();
    void detach();
    void set(int16_t messageID, char *payload);
    void update();

private:
    bool    _initialised;
};