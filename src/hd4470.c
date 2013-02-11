/*
 * hd44780.c
 *
 *  Created on: 31/01/2013
 *      Author: jared
 */


#include "hd44780.h"
#include "hd44780_imp.h"

#include "util/delay.h"

#define HD44780_CMD_HOME 0xAA
#define HD44780_CMD_OTHER

//
void hd44780_init(pin_struct RS, pin_struct RW, pin_struct EN, pin_struct* data)
{
	hd44780_init_imp(RS,RW,EN,data);
	//Set RS low
	SET_LOW(RS);
#ifdef HD44780_4BIT_MODE
	//Put into 4 bit mode
	hd44780_send_nibble(0x3);
	_delay_ms(5);
	hd44780_send_nibble(0x3);
	_delay_us(100);
	hd44780_send_nibble(0x3);
	_delay_us(100);
	hd44780_send_nibble(0x2);
	_delay_ms(5);
	hd44780_send_CMD(0x28);
#else
	//Send 8 bit mode initialisation
	hd44780_send_CMD(0x30);
	_delay_ms(5);
	hd44780_send_CMD(0x30);
	_delay_us(100);
	hd44780_send_CMD(0x30);
	_delay_us(100);
	hd44780_send_CMD(0x38);
#endif
	hd44780_send_CMD(0x08);
	hd44780_send_CMD(0x01);
	hd44780_send_CMD(0x06);
	hd44780_send_CMD(0x0C);
}

void hd44780_reset()
{

}

void hd44780_home()
{

}

void hd44780_clear()
{

}

void hd44780_write(char* data)
{

}
