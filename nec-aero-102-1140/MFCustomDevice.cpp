#include "MFCustomDevice.h"
#include "commandmessenger.h"
#include "allocateMem.h"
#include "MFEEPROM.h"
extern MFEEPROM MFeeprom;

/* **********************************************************************************
    The custom device pins, type and configuration is stored in the EEPROM
    While loading the config the adresses in the EEPROM are transferred to the constructor
    Within the constructor you have to copy the EEPROM content to a buffer
    and evaluate him. The buffer is used for all 3 types (pins, type configuration),
    so do it step by step.
    The max size of the buffer is defined here. It must be the size of the
    expected max length of these strings.

    E.g. 6 pins are required, each pin could have two characters (two digits),
    each pins are delimited by "|" and the string is NULL terminated.
    -> (6 * 2) + 5 + 1 = 18 bytes is the maximum.
    The custom type is "NecAeroScreen", which means 14 characters plus NULL = 15
    The configuration is "myConfig", which means 8 characters plus NULL = 9
    The maximum characters to be expected is 18, so MEMLEN_STRING_BUFFER has to be at least 18
********************************************************************************** */
MFCustomDevice::MFCustomDevice()
{
    _initialized = false;
}

void MFCustomDevice::attach(uint16_t adrPin, uint16_t adrType, uint16_t adrConfig)
{
    if (adrPin == 0) return;
        if (!FitInMemory(sizeof(NecAeroScreen))) {
            // Error Message to Connector
            cmdMessenger.sendCmd(kStatus, F("Custom Device does not fit in Memory"));
            return;
        }
        _mydevice = new (allocateMemory(sizeof(NecAeroScreen))) NecAeroScreen();
        _mydevice->attach();
        _initialized = true;
}

/* **********************************************************************************
    The custom devives gets unregistered if a new config gets uploaded.
    Keep it as it is, mostly nothing must be changed.
    It gets called from CustomerDevice::Clear()
********************************************************************************** */
void MFCustomDevice::detach()
{
    _initialized = false;
        _mydevice->detach();
}

/* **********************************************************************************
    Within in loop() the update() function is called regularly
    Within the loop() you can define a time delay where this function gets called
    or as fast as possible. See comments in loop().
    It is only needed if you have to update your custom device without getting
    new values from the connector.
    Otherwise just make a return; in the calling function.
    It gets called from CustomerDevice::update()
********************************************************************************** */
void MFCustomDevice::update()
{
    _mydevice->update();
}

/* **********************************************************************************
    If an output for the custom device is defined in the connector,
    this function gets called when a new value is available.
    It gets called from CustomerDevice::OnSet()
********************************************************************************** */
void MFCustomDevice::set(int16_t messageID, char *setPoint)
{
    if (!_initialized) return;
        _mydevice->set(messageID, setPoint);
}
