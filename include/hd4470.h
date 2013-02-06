/*
 * hd4470.h
 *
 *  Created on: 31/01/2013
 *      Author: jared
 *
 *	High level interface for controlling a HD4470 lcd display.
 *
 *	Usage:
 *	hd4470_init(pins);
 *
 *	If HD4470_SMART_WAIT is defined then the driver will poll the @todo pin to check
 *	when the device is ready for the next command. If it is not defined the driver will
 *	wait n ms.
 *
 *	Limitations: Only a single LCD per device
 *				Only operates in 4 pin mode
 */

#ifndef HD4470_H_
#define HD4470_H_

#include "pins.h"

/**
 * Initialises the pins and puts the HD4470 in a state to be written too
 * @param RS Reset Pin
 * @param RW Read/Write Pin
 * @param EN Enable Pin
 * @param data Data Pins. can contain either 4 or 8 pins.
 */
void hd4470_init(pin_struct RS, pin_struct RW, pin_struct EN, pin_struct* data);
/**
 * Resets the HD4470. Not sure if needed.
 */
void hd4470_reset();
/**
 * Returns the cursor to the home position
 */
void hd4470_home();

/**
 * Clears the screen
 */
void hd4470_clear();

/**
 * Writes some text to the screen from the current cursor location
 * @param data Null terminated string to write to the screen
 */
void hd4470_write(char *data);

#endif /* HD4470_H_ */
