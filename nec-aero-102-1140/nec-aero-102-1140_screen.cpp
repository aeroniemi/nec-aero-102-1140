#include "nec-aero-102-1140_screen.h"

Display::Display()
{
    resetDisplay();
}

void Display::setText(int row, String text)
{
    for (int i = 0; i < text.length(); i++)
    {
        int value = String(text.charAt(i)).toInt();
        int *segments = charsToSegments[value];
        // std::cout << value; //<< charsToSegments[4][1];

        for (int j = 0; j < 7; j++)
        {
            if (segments[j] > 0)
            {
                setSegment(row, i + 1, segments[j] - 1);
            }
        }
    }
}

void Display::resetDisplay()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            displayBuffer[i][j] = 0x00;
        }
    }
    addDots();
}

void Display::setSegment(int row, int col, int ident)
{
    // std::cout << " A segment " << ident;
    Segment segment = getSegmentValue(row, col, ident);
    displayBuffer[segment.subaddr][segment.block] |= segment.value;
}

Segment Display::getSegmentValue(int row, int col, int ident)
{
    return segmentToByte[row][col][ident];
}

void Display::addDots()
{
    setSegment(0, 0, 1); // UPPER DOT
    setSegment(1, 0, 1); // LOWER DOT
    setSegment(0, 0, 0); // TX
    setSegment(1, 0, 0); // ARROW
}

void Display::update()
{
    // Implement your update logic here
    //Serial.print("\n");
    for (size_t i = 0; i < numSubAddr; i++)
    {
        write(i);
    }
}
void Display::write(int subaddr)
{
    uint8_t controlRegister = 0;
    controlRegister |= (0x0) ? 0x80 : 0x00;
    controlRegister |= (subaddr & 0x7) << 3;
    Wire.beginTransmission(0x3A);
    Wire.write(controlRegister);
    Wire.write(displayBuffer[subaddr], 4);
    Wire.endTransmission();
}