/**
 * \file pins.h
 *
 * \author Jared Lewis (jared at bodekerscientific dot com)
 * \date 14/01/2013
 *
 * Header file that contains pin definitions and any associated declarations
 *
 */

#ifndef PINS_H_
#define PINS_H_

#include "misc.h"

/**
 * Enum for the possible allocation of each pin
 *
 * @TODO Fill this with all possibilities
 */
enum PinAssignment {
	PIN_UNUSED,//!< PIN_UNUSED 	Currently unused/unassigned pin
	PIN_GPIO,  //!< PIN_GPIO	General purpose pin
	PIN_ADC,   //!< PIN_ADC
	PIN_DAC    //!< PIN_DAC
};

typedef enum {
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E
} PinPort;
typedef unsigned int PinNum;

/**
 * Struct to represent a single pin
 * Care should be taken when manipulating the contents directly, instead see getPin
 *
 * This struct may change at anytime.
 *
 * @note I don't really like the fact that each pin struct needs 3 reg pointers associated with it. Potential waste of memory
 *
 * @see getPin
 */
typedef struct {
	PinPort portID;		//!< Port identifier
	PinNum pinID;		//!< Pin Number
	uint8_t address; 	//!< Memory address of the pin
	uint8_t dirAddr;	//!< Data Direction Register
	uint8_t inAddr;	//!< Input Register
} pin_struct;

/**
 * Retrieves the pin_struct for a given port and pin. Care must be taken to not change any values as this may have unwanted
 * side effects.
 * @param port Port Number
 * @param num Pin number
 * @return The pointer the the pin_struct
 */
pin_struct get_pin(PinPort port, PinNum num);

/**
 * Queries the current state of a pin
 * @param pin Struct for the target pin
 * @return True if the target pin is high
 */
bool get_state(pin_struct pin);

/**
 * Sets the direction of a single pin
 * @param pin Target pin
 * @param isOutput True if the pin is to be set to an output
 */
void set_output(pin_struct pin, bool isOutput);

/**
 * Sets the state of a single pin to be either high or low
 * @param pin Pointer to the pin_struct
 * @param state State to set the pin (True == high)
 */
void set_pin(pin_struct pin, bool state);

/**
 * Sets the state of an array of n pins to value
 * @param pins Array of pins. Should be null terminated
 * @param value Value to mask pins to
 * @param n Number of pins to mask
 */
void set_pins(pin_struct* pins, unsigned int value, unsigned int n);

#endif /* PINS_H_ */
