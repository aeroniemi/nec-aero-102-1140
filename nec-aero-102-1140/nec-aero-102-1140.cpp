#include "nec-aero-102-1140.h"
#include "allocateMem.h"
#include "commandmessenger.h"

Display display;

NecAeroScreen::NecAeroScreen()
{
}


void NecAeroScreen::attach()
{
Wire.begin();
display.update();
}

void NecAeroScreen::detach()
{
    if (!_initialised)
        return;
    Wire.end();
    _initialised = false;
}

void NecAeroScreen::set(int16_t messageID, char *payload)
{
   if (messageID == 0) {
        String text = String(payload);
        String top = text.substring(0, 6);
        String bottom = text.substring(7, 14);
        display.resetDisplay();
        display.setText(0,top);
        display.setText(1,bottom);
        display.update();
    }
}

void NecAeroScreen::update() {
    display.update();
}