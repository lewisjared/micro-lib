/*
 * hd44780_imp.c
 *
 *  Created on: 6/02/2013
 *      Author: jared
 */

#include "hd44780_imp.h"
#include "misc.h"

#include "util/delay.h"

#ifdef HD44780_4BIT_MODE
#define HD44780_NUM_DATA 4
#else
#define HD44780_NUM_DATA 8
#endif

#define DELAY_LENGTH_US 100
#define RS_DATA 1
#define RS_CMD 0

//Static local variables
static pin_struct s_RS;
static pin_struct s_RW;
static pin_struct s_EN;
static pin_struct* s_data;

void hd44780_init_imp(pin_struct RS, pin_struct RW, pin_struct EN, pin_struct* data)
{
	//Assign the variables
	s_RS = RS;
	s_RW = RW;
	s_EN = EN;
	s_data = data;

	//Set the direction of the pins
	SET_OUT(RS);
	SET_OUT(RW);
	SET_OUT(EN);

	for (int i = 0; i < HD44780_NUM_DATA; i++)
		SET_OUT(data[i]);
}

void hd44780_clock_in()
{
	SET_HIGH(s_EN);
	//@todo check what this should be
	_delay_us(DELAY_LENGTH_US);
	SET_LOW(s_EN);
}

void hd44780_send_byte(uint8_t data)
{
#ifdef HD44780_4BIT_MODE
	//Write low bits first
	hd44780_send_nibble(data);
	//Next send the high bits
	hd44780_send_nibble((0xF0 & data) >> 4);
#else
	//8 bit mode
	// Write 8 bits to the buffer
	set_pins(s_data, data, 8);
	hd44780_clock_in();
#endif
}

void hd44780_send_nibble(uint8_t data)
{
	set_pins(s_data,0x0F & data, 4);
	hd44780_clock_in();
}

void hd44780_send_data(uint8_t data)
{
	set_pin(s_RS, RS_DATA);
	hd44780_send_byte(data);
}

void hd44780_send_CMD(uint8_t data)
{
	set_pin(s_RS, RS_CMD);
	hd44780_send_byte(data);
}
