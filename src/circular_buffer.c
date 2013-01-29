/**
 * \file circular_buffer.c
 *
 * \author Jared Lewis (jared at bodekerscientific dot com)
 * \date 29/01/2013
 *
 * Definition of circular buffer functions
 *
 * @note Since malloc is used to allocate memory
 */

#include "circular_buffer.h"


circ_buffer circ_init(uint8_t length)
{
	circ_buffer buff;
	buff.length = length;

	//Note Allocates using malloc
	//@todo check for buff.data = NULL
	buff.data = (uint8_t*) malloc(length*sizeof(uint8_t));

	//Zero the read and write pointers
	buff.rP = 0;
	buff.wP = 0;

	return (buff);
}

//Fixed size allocation
circ_buffer circ_init_fixed()
{
	///@note that this actually DOES use malloc
	return (circ_init(CIRC_FIXED_SIZE));
}

void circ_free(circ_buffer *buffer)
{
	free(buffer->data);
	//Releases data address
	buffer->data = 0;
}
