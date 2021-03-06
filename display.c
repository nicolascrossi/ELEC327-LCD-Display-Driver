/*
 * display.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Nicolas Rossi
 */
#include "display.h"

char *txt;
unsigned int txtLen;
volatile unsigned int idx;
volatile bool done;

char clear[2] = {0x0D, 0x0D};

void initDisplay() {
    if (CALBC1_1MHZ==0xFF)   // If calibration constant erased
    {
        while(1);          // do not load, trap CPU!!
    }

    DCOCTL  = 0;             // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;   // Set range
    DCOCTL  = CALDCO_1MHZ;   // Set DCO step + modulation

    P1SEL |= BIT2;
    P1SEL2 |= BIT2;

    UCA0CTL1 |=  UCSSEL_2 + UCSWRST;  // USCI Clock = SMCLK,USCI_A0 disabled
    UCA0BR0   =  104;                 // 104 From datasheet table-
    UCA0BR1   =  0;                   // -selects baudrate =9600,clk = SMCLK
    UCA0MCTL  =  UCBRS_1;             // Modulation value = 1 from datasheet
    UCA0CTL1 &= ~UCSWRST;             // Clear UCSWRST to enable USCI_A0

//    IE2 |= UCA0TXIE;                  // Enable the Transmit interrupt

    _BIS_SR(GIE);                     // Enable the global interrupt

    done = true;
}


void printBytes(char *str, unsigned int len) {
    if (len == 0) {
        done = true;
        return;
    }

    txt = str;
    txtLen = len;
    idx = 0;
    done = false;
    IE2 |= UCA0TXIE; // Enable the Transmit interrupt

//    txt = str + 1;
//
//    if (str[0] == '\0') {
//        done = true;
//        return;
//    } else {
//        done = false;
//    }
//
//    UCA0TXBUF = *str;
}

bool donePrinting() {
    return done;
}

void clearDisplay() {
    printBytes(clear, 2);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCIAB0TX_VECTOR
__interrupt void TransmitInterrupt(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) watchdog_timer (void)
#else
#error Compiler not supported!
#endif
{
    if (idx >= txtLen) {
        IE2 &= ~UCA0TXIE; // Disable the Transmit interrupt
        done = true;
    } else {
        UCA0TXBUF = txt[idx++];
    }

//    if (*txt != '\0') {
//        UCA0TXBUF = *txt++;
//    } else {
//        done = true;
//    }
//    IFG2 &= ~UCA0TXIFG;
}
