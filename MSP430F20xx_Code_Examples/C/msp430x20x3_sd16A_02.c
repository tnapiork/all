/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 * 
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430F20x3 Demo - SD16, Using the Integrated Temperature Sensor
//
//  Description: Use SD16 and it's integrated temperature sensor to detect
//  temperature delta. The temperature sensor output voltage is sampled
//  ~ every 240ms and compared with the last value and if more than ~0.5C
//  delta, P1.0 is set, else reset.
//  SD16 Internal VRef, Bipolar offset binary output format used.
//  Watchdog used as interval time and ISR used to start next SD16 conversion.
//  ACLK = n/a, MCLK = default DCO, SMCLK = SD16CLK = default DCO/8
//
//                MSP430F20x3
//             ------------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A6+              |
//            |A6-          P1.0|-->LED
//            |                 |
//
//  M. Buccini / L. Westlund
//  Texas Instruments Inc.
//  October 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.40A
//******************************************************************************
#include <msp430.h>

#define ADCDeltaOn 31                       // ~0.5 Deg C delta
static unsigned int LastADCVal;             // holds ADC temperature result

int main(void)
{
  BCSCTL2 |= DIVS_3;                        // SMCLK/8
  WDTCTL = WDT_MDLY_32;                     // WDT Timer interval
  IE1 |= WDTIE;                             // Enable WDT interrupt
  P1DIR |= 0x01;                            // P1.0 to output direction
  SD16CTL = SD16REFON +SD16SSEL_1;          // 1.2V ref, SMCLK
  SD16INCTL0 = SD16INCH_6;                  // A6+/-
  SD16CCTL0 = SD16SNGL + SD16IE ;           // Single conv, interrupt

  _BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 with interrupt
}

#pragma vector=SD16_VECTOR
__interrupt void SD16ISR(void)
{
  if (SD16MEM0 <= LastADCVal + ADCDeltaOn)
    P1OUT &= ~0x01;                         // LED off
  else
    P1OUT |= 0x01;                          // LED on
  LastADCVal = SD16MEM0;                    // Store value
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  SD16CCTL0 |= SD16SC;                      // Start SD16 conversion
}


