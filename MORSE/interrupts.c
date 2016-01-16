/*
 * interrupts.c
 *
 *  Created on: 18 Dec 2015
 *      Author: offic
 */
#include <msp430.h>
#include "main.h"
#include "interrupts.h"
#include "setup.h"

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer (void) {

	// we are in the interrupt so we need to up our counter
	counter++;

	// now process any waiting
	if (waitingForInput) {					// flash green when waiting for input
		if (counter >= READY_BLINK_TIME) {
			LEDS_OUT ^= GREEN_LED;			// toggle LED
			counter = 0;
		}
	} else if (error) {						// red on long when error
		if (counter >= ERROR_ON_TIME) {
			LEDS_OUT &= ~RED_LED;			// red off
			process_reset = TRUE;
			error = FALSE;
			counter = 0;
		}
	} else if (wordRecognised) {			// long green when recognised
		if (counter >= WORD_RECOGNISED_ON_TIME) {
			LEDS_OUT &= ~GREEN_LED;			// green off
			process_reset = TRUE;
			counter = 0;
		}
	} else if (ditRecognised | dashRecognised) {	// short blink of red when recognised
		if (counter >= DIT_RECOGNISED_ON_TIME) {
			LEDS_OUT &= ~RED_LED;			// red off
			ditRecognised = FALSE;
			dashRecognised = FALSE;
			counter = 0;
		}
	} else if (counter > (WORD_PAUSE_MAX + LONG_PRESS_MAX)) {  // red and green when timeout
		counter = 0;
		LEDS_OUT |= RED_LED;			// red on
		LEDS_OUT |= GREEN_LED;			// green on
		error = TRUE;
		counter = 0;
	} else if (counter > WORD_PAUSE_MAX) {					   // we MIGHT just have a letter pause so
		if (!spaceRecognised) {  // only one space at a time
			LEDS_OUT |= RED_LED;			// red on
			ditRecognised = TRUE;
			counter = 0;
			spaceRecognised = TRUE;
			if (SPACE == wordToCheck [index]) {
				index++;  // we start counting at 0 so add first when checking the length
				if (index == sizeOfWord) { // the word could end in a space ???
					wordRecognised = TRUE;
					LEDS_OUT &= ~RED_LED;			// red off again as you have recognised the word!
					LEDS_OUT |= GREEN_LED;			// green on
				}
			} else {
				LEDS_OUT |= RED_LED;			// red on
				error = TRUE;
			}
		}
	}

}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void process_button_press (void) {

	// button pressed so we are now no longer waiting for input!
	waitingForInput = FALSE;
	LEDS_OUT &= ~GREEN_LED;			// turn off green

	if (button_pressed) {
		process_button_pressed = TRUE;
	} else {
		button_pressed = TRUE;
		process_button_pressed = FALSE;
		error = FALSE;
		counter = 0;
	}

	// toggle high / low transition
	BUTTON_IES ^= BUTTON;

	// remove interrrupt flag so you can process the next one
	BUTTON_IFG &= ~BUTTON;

}
