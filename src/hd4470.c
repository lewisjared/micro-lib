/*
 * hd4470.c
 *
 *  Created on: 31/01/2013
 *      Author: jared
 */


#include "hd4470.h"
#include "hd4470_imp.h"

#include "util/delay.h"

#define HD4470_CMD_HOME 0xAA
#define HD4470_CMD_OTHER

//
void hd4470_init(pin_struct RS, pin_struct RW, pin_struct EN, pin_struct* data)
{
	hd4470_init_imp(RS,RW,EN,data);
	//Set RS low
	SET_LOW(RS);
#ifdef HD4470_4BIT_MODE
	//Put into 4 bit mode
	hd4470_send_nibble(0x3);
	_delay_ms(5);
	hd4470_send_nibble(0x3);
	_delay_us(100);
	hd4470_send_nibble(0x3);
	_delay_us(100);
	hd4470_send_nibble(0x2);
	_delay_ms(5);
	hd4470_send_CMD(0x28);
#else
	//Send 8 bit mode initialisation
	hd4470_send_CMD(0x30);
	_delay_ms(5);
	hd4470_send_CMD(0x30);
	_delay_us(100);
	hd4470_send_CMD(0x30);
	_delay_us(100);
	hd4470_send_CMD(0x38);
#endif
	hd4470_send_CMD(0x08);
	hd4470_send_CMD(0x01);
	hd4470_send_CMD(0x06);
	hd4470_send_CMD(0x0C);
}

void hd4470_reset()
{

}

void hd4470_home()
{

}

void hd4470_clear()
{

}

void hd4470_write(char* data)
{

}
