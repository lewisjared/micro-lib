/**
 * \file pins.c
 *
 * \author Jared Lewis (jared at bodekerscientific dot com)
 * \date 14/01/2013
 *
 * Function declaration for the interface to the pins
 *
 */

/**
 * @note Maybe change pin_struct to be passed as const refs rather than by value
 * 		Maybe look at generated code to see any difference. gcc may be smart enough
 */

#include "pins.h"
#include "avr/io.h"


pin_struct get_pin(PinPort port, PinNum num)
{
	pin_struct pin;
	pin.portID = port;
	pin.pinID = num;

	// Determine register addresses
	switch(port)
	{
	case PORT_A:
		#ifdef PORTA
			pin.address = PORTA;
			pin.dirAddr = DDRA;
			pin.inAddr = PINA;
		#endif
		break;
	case PORT_B:
		pin.address = PORTB;
		pin.dirAddr = DDRB;
		pin.inAddr = PINB;
		break;
	case PORT_C:
		pin.address = PORTC;
		pin.dirAddr = DDRC;
		pin.inAddr = PINC;
		break;
	case PORT_D:
		pin.address = PORTD;
		pin.dirAddr = DDRD;
		pin.inAddr = PIND;
		break;
	default:
		pin.address = 0;
		pin.dirAddr = 0;
		pin.inAddr = 0;
		break;
	}
	return (pin);
}

bool get_state(pin_struct pin)
{
	return ((bool) pin.inAddr & BIT(pin.pinID));
}

void set_output(pin_struct pin, bool isOutput)
{
	if (isOutput == true)
		BIT_SET(pin.dirAddr, pin.pinID);
	else
		BIT_RESET(pin.dirAddr, pin.pinID);
}

void set_pin(pin_struct pin, bool state)
{
	if (state == true)
		BIT_SET(pin.address, pin.pinID);
	else
		BIT_RESET(pin.address, pin.pinID);
}

void set_pins(pin_struct* pins, unsigned int value, unsigned int n)
{
	unsigned int count = 0;

	//Assuming that the array is NULL terminated
	while (pins != NULL && count < n)
	{
		set_pin(*pins, (value >> (n-count)));
		pins++;
		count++;
	}
}
