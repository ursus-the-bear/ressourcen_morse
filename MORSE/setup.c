/*
 * setup.c
 *
 *  Created on: 18 Dec 2015
 *      Author: offic
 */
#include <msp430.h>
#include "main.h"
#include "interrupts.h"
#include "setup.h"

void setup_timer (void) {

	// This sets the MSP430's clock to a factory calibrated 1 MHz,
	// which means that any delays we specify will be more accurate
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;

	// Setup your timer
	TA0CCTL1 = CM_0 | OUTMOD_7;		// no capture (->ignore CCISx, SCS, SCCI), Compare mode, Reset/Set outmode, ignore "rest"
	CCTL0 = CCIE;					// CCRO Interrupt enable
	TA0CTL = 						// Timer TA0
			TASSEL_2 +				// TASSEL_2 selects SMCLK clock
			ID_0 + 					// ???
			MC_1 + 					// ???
			TACLR;					// Clear timer
	TACCR0 = 1000; 					// 1 ms @ 1MHz

}

void setup_button (void) {

	// Button setup
	P1DIR &= ~BUTTON; 				// button is an input
	P1OUT |= BUTTON; 				// pull-up resistor
	P1REN |= BUTTON; 				// resistor enabled
	BUTTON_IES |= BUTTON; 			// high-to-low transition
	BUTTON_IFG &= ~BUTTON; 			// clear eventual interrupt status (floating gate)
	BUTTON_IE |= BUTTON; 			// enable module interrupt

}

void setup_LEDs (void) {
	// LED initial setup
	P1DIR |= RED_LED + GREEN_LED;	// set P1DIR out for RED and GREEN
	LEDS_OUT &= ~RED_LED;			// turn off red
	LEDS_OUT &= ~GREEN_LED;			// turn off green

}
