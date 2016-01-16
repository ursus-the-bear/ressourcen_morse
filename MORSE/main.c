#include <msp430.h>
#include "main.h"
#include "interrupts.h"
#include "setup.h"

const char wordToCheck [] = {DIT, DIT, DIT, DIT, SPACE, DIT, DIT};	// Hi
// const char wordToCheck [] = {DIT, DIT, DIT};	// Hi

// we are waitingForInput to accept some morse code
void ready_to_morse (void) {

	// we are now waiting for input
	waitingForInput = TRUE;
	counter = 0;
	button_pressed = FALSE;
	process_button_pressed = FALSE;
	process_reset = FALSE;
	error = FALSE;
	ditRecognised = FALSE;
	dashRecognised = FALSE;
	spaceRecognised = FALSE;
	index = 0;
	wordRecognised = FALSE;

	// cleanup LED's in case they are on
	LEDS_OUT &= ~RED_LED;			// turn off red
	LEDS_OUT &= ~GREEN_LED;			// turn off green

}
void process_button (void) {

	// do not process interrupts when I am busy
	_disable_interrupts();

	//	if ((counter >= SHORT_PRESS_MIN) && (counter <= SHORT_PRESS_MAX)) {
	if (counter <= SHORT_PRESS_MAX) {
		LEDS_OUT |= RED_LED;			// red on
		ditRecognised = TRUE;
		if (DIT == wordToCheck [index]) {
			index++;  // we start counting at 0 so add first when checking the length
			if (index == sizeof (wordToCheck)) {
				wordRecognised = TRUE;
				LEDS_OUT &= ~RED_LED;			// red off again as you have recognised the word!
				LEDS_OUT |= GREEN_LED;			// green on
			}
		} else {
			LEDS_OUT |= RED_LED;			// red on
			error = TRUE;
		}
		//	} else if ((counter <= LONG_PRESS_MIN) && (counter >= LONG_PRESS_MAX)) {
	} else if (counter <= LONG_PRESS_MAX) {
		LEDS_OUT |= RED_LED;			// red on
		ditRecognised = TRUE;
		if (DAH == wordToCheck [index]) {
			index++;  // we start counting at 0 so add first when checking the length
			if (index == sizeof (wordToCheck)) {
				wordRecognised = TRUE;
				LEDS_OUT &= ~RED_LED;			// red off again as you have recognised the word!
				LEDS_OUT |= GREEN_LED;			// green on
			}
		} else {
			LEDS_OUT |= RED_LED;			// red on
			error = TRUE;
		}
	} else {
		LEDS_OUT |= RED_LED;			// red on
		error = TRUE;
	}

	// reset your flags so you can process the next press
	button_pressed = FALSE;
	process_button_pressed = FALSE;
	counter = 0;

	// ok, now we can process interrupts again
	_enable_interrupts ();

}

void main(void) {

	// needed to do this as I could not check sizeof in the interrupts routine? maybe ask about this?
	sizeOfWord = sizeof (wordToCheck);

	// Watchdog setup
	WDTCTL = WDTPW + WDTHOLD; 		// stop using the watchdog

	// setup your various functions
	setup_LEDs ();
	setup_timer ();
	setup_button ();

	// enable your interrupts
	_enable_interrupts();

	// tell the user you are waitingForInput
	ready_to_morse();

	while (TRUE){
		if (process_button_pressed)
			process_button ();
		if (process_reset)
			ready_to_morse();
	}

	// we will never get here

}
