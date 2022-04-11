#include "msp430g2553.h"

#include "display.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog

    // Strings to display. Extra space probably only required for strings.
    char oneChar[2] = "h";
    char newLine[2] = "\r";
    char greeting[6] = "hello";
    // For setting the back light color
    char white[5] = {0xFE, 0xD0, 0xFF, 0xFF, 0xFF};
    char red[5] = {0xFE, 0xD0, 0xFF, 0x00, 0x00};
    char green[5] = {0xFE, 0xD0, 0x00, 0xFF, 0x00};
    char blue[5] = {0xFE, 0xD0, 0x00, 0x00, 0xFF};

    initDisplay();  // Initialize the display

    clearDisplay(); // Clear the display. Important if the display has not been power cycled since last run

    while(!donePrinting()); // Inefficient way to wait for the end of writing

    printBytes(white, 5);

    while(!donePrinting());

    printBytes(oneChar, 1);

    while(!donePrinting());

    printBytes(newLine, 1);

    while(!donePrinting());

    printBytes(greeting, 5);

    while(!donePrinting());

//    printBytes(red, 5);


   _BIS_SR(LPM0_bits + GIE);         // Going to LPM0
}
