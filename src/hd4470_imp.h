/*
 * hd4470_imp.h
 *
 *  Created on: 6/02/2013
 *      Author: jared
 *
 * This file contains the private declaritions for the low level functions of the HD4470
 * driver. The user should not directly use these functions
 */

#ifndef HD4470_IMP_H_
#define HD4470_IMP_H_


/**
 * Initialises the pins to the correct type etc
 * @param RS
 * @param RW
 * @param EN
 * @param data
 */
void hd4470_init_imp(pin_struct RS, pin_struct RW, pin_struct EN, pin_struct* data);
/**
 * Clocks in the current data on the bus to the device
 */
void hd4470_clock_in();

/**
 * Places a byte on the data bus
 * @param data
 */
void hd4470_send_byte(uint8_t data);


#ifdef HD4470_4BIT_MODE
/**
 * Sends the lower 4 bits of data to the device. Only needed if the device is
 * in 4 bit mode.
 * @param data Nibble of data
 */
void hd4470_send_nibble(uint8_t data);
#endif //HD4470_4BIT_MODE
/**
 * Sets the device to be ready for data
 */
void hd4470_set_data();

/**
 * Sets the device to be ready for a command
 */
void hd4470_set_CMD();



#endif /* HD4470_IMP_H_ */
