/**
 * \file circular_buffer.c
 *
 * \author Jared Lewis (jared at bodekerscientific dot com)
 * \date 29/01/2013
 *
 * Definition of circular buffer functions
 *
 * This buffer uses the keep one slot free implementation (http://en.wikipedia.org/wiki/Circular_buffer#Always_Keep_One_Slot_Open)
 * This allows easy testing for full and empty while keeping the circ buffer struct small.
 *
 */

#include "circular_buffer.h"

#include <stdlib.h>

//Macro for incrementing a pointer and wrapping if necessary
#define CIRC_INC(item, length)	item = (item + 1) % length


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

uint8_t circ_read(circ_buffer *buffer)
{
	uint8_t val = buffer->data[buffer->rP];
	//increment pointer and wrap if necessary
	CIRC_INC(buffer->rP,buffer->length);
	return (val);
}

void circ_write(circ_buffer *buffer, uint8_t value)
{
	buffer->data[buffer->wP] = value;
	CIRC_INC(buffer->wP, buffer->length);
	//Check if over full and overwrite if necessary
	if (buffer->rP == buffer->wP)
		CIRC_INC(buffer->rP, buffer->length);
}

/// Buffer is empty if the read pointer and the write pointer point to
/// the same location
bool ci_brc_is_empty(const circ_buffer *buffer)
{
	return (buffer->rP == buffer->wP);
}

bool circ_is_full(const circ_buffer *buffer)
{
	/// Buffer is full if the write pointer points to the location before the read pointer
	return ((buffer->wP+1) % buffer->length == buffer->rP);
}
