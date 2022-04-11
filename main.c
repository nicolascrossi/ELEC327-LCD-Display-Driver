#include "msp430g2553.h"

#include "display.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop the Watch dog

    // Strings to display. Note the extra length for the null byte.
    char oneChar[2] = "h";
    char newLine[2] = "\r";
    char greeting[6] = "hello";

    initDisplay();  // Initialize the display

    clearDisplay();

    while(!donePrinting());

    printString(oneChar);

    while(!donePrinting());

    printString(newLine);

    while(!donePrinting());

    printString(greeting);

   _BIS_SR(LPM0_bits + GIE);         // Going to LPM0
}
