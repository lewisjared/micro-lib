/*
 * hd44780.h
 *
 *  Created on: 31/01/2013
 *      Author: jared
 *
 *	High level interface for controlling a HD44780 lcd display.
 *
 *	Usage:
 *	hd44780_init(pins);
 *
 *	If HD44780_SMART_WAIT is defined then the driver will poll the @todo pin to check
 *	when the device is ready for the next command. If it is not defined the driver will
 *	wait n ms.
 *
 *	Limitations: Only a single LCD per device
 *				Only operates in 4 pin mode
 */

#ifndef HD44780_H_
#define HD44780_H_

#include "pins.h"

/**
 * Initialises the pins and puts the HD44780 in a state to be written too
 * @param RS Reset Pin
 * @param RW Read/Write Pin
 * @param EN Enable Pin
 * @param data Data Pins. can contain either 4 or 8 pins.
 */
void hd44780_init(pin_struct RS, pin_struct RW, pin_struct EN, pin_struct* data);
/**
 * Resets the HD44780. Not sure if needed.
 */
void hd44780_reset();
/**
 * Returns the cursor to the home position
 */
void hd44780_home();

/**
 * Clears the screen
 */
void hd44780_clear();

/**
 * Writes some text to the screen from the current cursor location
 * @param data Null terminated string to write to the screen
 */
void hd44780_write(char *data);

#endif /* HD44780_H_ */
