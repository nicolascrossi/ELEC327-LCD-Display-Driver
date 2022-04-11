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

    clearDisplay(); // Clear the display. Important if the display has not been power cycled since last run

    while(!donePrinting()); // Inefficient way to wait for the end of writing

    printString(oneChar);

    while(!donePrinting());

    printString(newLine);

    while(!donePrinting());

    printString(greeting);

   _BIS_SR(LPM0_bits + GIE);         // Going to LPM0
}
