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
//  MSP430F20x2 Demo - ADC10, DTC Sample A10 32x, 1.5V, Repeat Single, DCO
//
//  Description: Use DTC to sample A10 32 times with reference to internal 1.5v.
//  Vref Software writes to ADC10SC to trigger sample burst. In Mainloop MSP430
//  waits in LPM0 to save power until ADC10 conversion complete, ADC10_ISR(DTC)
//  will force exit from any LPMx in Mainloop on reti. (ADC10OSC/4)/64
//  determines sample time which needs to be greater than 30us for temperature
//  sensor. DTC transfers conversion code to RAM 200h - 240h. P1.0 set at start
//  of conversion burst, reset oncompletion. Temperature sensor offset and slope
//  will vary from device to device per datasheet tolerance.
//
//                MSP430F20x2
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |A10          P1.0|-->LED
//
//  L. Westlund
//  Texas Instruments Inc.
//  May 2006
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.41A
//******************************************************************************
#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL1 = INCH_10 + ADC10DIV_3 + CONSEQ_2;
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + MSC + REFON + ADC10ON + ADC10IE;
  __enable_interrupt();                     // Enable interrupts.
  TACCR0 = 30;                              // Delay to allow Ref to settle
  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
  TACTL = TASSEL_2 + MC_1;                  // TACLK = SMCLK, Up mode.
  LPM0;                                     // Wait for delay.
  TACCTL0 &= ~CCIE;                         // Disable timer Interrupt
  __disable_interrupt();
  ADC10DTC1 = 0x20;                         // 32 conversions
  P1DIR |= 0x01;                            // Set P1.0 output

  for (;;)
  {
    ADC10CTL0 &= ~ENC;                      //
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    P1OUT |= 0x01;                          // P1.0 = 1
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    P1OUT &= ~0x01;                         // P1.0 = 0
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

#pragma vector=TIMERA0_VECTOR
__interrupt void ta0_isr(void)
{
  TACTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}
