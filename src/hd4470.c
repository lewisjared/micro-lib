/*
 * hd4470.c
 *
 *  Created on: 31/01/2013
 *      Author: jared
 */


#include "hd4470.h"
#include "hd4470_imp.h"

//Static local variables
static pin_struct s_RS;
static pin_struct s_RW;
static pin_struct s_EN;
static pin_struct s_data;

#define HD4470_CMD_HOME 0xAA
#define HD4470_CMD_OTHER

//
void hd4470_init(pin_struct RS, pin_struct RW, pin_struct EN, pin_struct* data)
{


	//Set the
}
