/*
 * mail.h
 *
 *  Created on: 18 Dec 2015
 *      Author: offic
 */

#ifndef MAIN_H_
#define MAIN_H_

#define DIT '.'
#define DAH '.'
#define SPACE ' '
int index;
int sizeOfWord;

int waitingForInput;			// are we ready to process key presses
int counter;					// counter used in timer interrupt

int button_pressed;				// has the button been pressed
int error;						// we have a error

// the process flags are used so we do not stay in the interrupts to long
int process_button_pressed;		// we have a button pressed
int process_reset;				// we need to reset after an error
int ditRecognised;				// guess
int dashRecognised;				// guess
int wordRecognised;				// ditto
int spaceRecognised;			// need to check for spaces

#define TRUE 1==1
#define FALSE !TRUE

#define BUTTON BIT3 // Port 1.3

#define LEDS_OUT P1OUT
#define LEDS_DIR P1DIR
#define RED_LED BIT0 // Port 1.0
#define GREEN_LED BIT6 // Port 1.6

#define BUTTON_IE P1IE
#define BUTTON_IFG P1IFG
#define BUTTON_IES P1IES

#define SHORT_PRESS_MSEC 110
#define LETTER_PAUSE_MSEC SHORT_PRESS_MSEC
#define LONG_PRESS_MSEC 3 * SHORT_PRESS_MSEC
#define WORD_PAUSE_MSEC	7 * SHORT_PRESS_MSEC

#define SHORT_PRESS_MIN SHORT_PRESS_MSEC * 0.9
#define SHORT_PRESS_MAX SHORT_PRESS_MSEC * 1.1

#define LONG_PRESS_MIN LONG_PRESS_MSEC * 0.9
#define LONG_PRESS_MAX LONG_PRESS_MSEC * 1.1

#define WORD_PAUSE_MIN WORD_PAUSE_MSEC * 0.9
#define WORD_PAUSE_MAX WORD_PAUSE_MSEC * 1.1

#define READY_BLINK_TIME 500				// 1/2 seconds
#define DIT_RECOGNISED_ON_TIME 250			// 1/4 seconds
#define ERROR_ON_TIME 5000	 				// 10 seconds is too long, rather wait 5 seconds
#define WORD_RECOGNISED_ON_TIME 10000	 	// 10 seconds

#endif /* MAIN_H_ */
