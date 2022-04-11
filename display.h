/*
 * display.h
 *
 *  Created on: Apr 10, 2022
 *      Author: Nicolas Rossi
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdbool.h>
#include <msp430g2553.h>

// Initialize everything required for the display.
void initDisplay(void);

// Print the given null terminated string to the display.
void printString(char *);

// Returns true if the current print has finished.
bool donePrinting(void);

void clearDisplay(void);

#endif /* DISPLAY_H_ */
