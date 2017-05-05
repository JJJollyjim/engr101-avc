#include <stdio.h>
#include <stdio.h>
#include "E101.h"

/*
	- assumes that the main class initialises the RPi.
	- will need to rename sensor pin globals if we use multiple sensors of one type.
*/

/* Global variables */
int SHORT_RANGE_IR_PIN = 0; // analog pin which the IR sensor is connected to.
int MED_RANGE_IR_PIN = 0;
int PUSH_BUTTON_PIN = 0;

/* Raw readings */

double readShortRangeIR() {
	double value = read_analog(IR_PIN);
	return value;
}

double readMedRangeIR() {
	double value = read_digital(MED_RANGE_IR_PIN);
	return value;
}

Boolean readPushButton() {
	// assumes a push button is either ON or OFF, unsure if this is correct atm.
	int value = read_digital(PUSH_BUTTON_PIN);

	if (value == 1) {
		return true;
	}
	else {
		return false;
	}
}

/* Average readings */

