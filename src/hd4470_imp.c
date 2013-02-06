/*
 * hd4470_imp.c
 *
 *  Created on: 6/02/2013
 *      Author: jared
 */

#include "hd4470_imp.h"

//Static local variables
static pin_struct s_RS;
static pin_struct s_RW;
static pin_struct s_EN;
static pin_struct s_data;

void hd4470_init_imp(pin_struct RS, pin_struct RW, pin_struct EN, pin_struct* data)
{
	//Assign the variables
	s_RS = RS;
	s_RW = RW;
	s_EN = EN;
	s_data = data;

	//Set the direction of the pins
}

void hd4470_clock_in()
{

}
