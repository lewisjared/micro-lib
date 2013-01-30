/**
 * \file circular_buffer.h
 *
 * \author Jared Lewis (jared at bodekerscientific dot com)
 * \date 29/01/2013
 *
 * Public interface for circular buffer. Implements a simple circular buffer of variable length
 * @todo Ensure this is reentrant
 */

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include "misc.h"

/**
 * Struct that represents a circular buffer.
 */
typedef struct {
	uint8_t length;	//!< Length of buffer
	uint8_t rP;		//!< Read Pointer
	uint8_t wP;		//!< Write Pointer
	uint8_t* data;	//!< Data Array
}circ_buffer;

#define CIRC_FIXED_SIZE 30

/**
 * Initialises a empty circular buffer with a given length
 * @param length Length of buffer
 * @return Buffer struct
 */
circ_buffer circ_init(uint8_t length);

/**
 * Initialises a circular buffer of fixed length, CIRC_FIXED_SIZE.
 * This does not use malloc to allocate, therefore free should not be called.
 * @return Buffer
 */
circ_buffer circ_init_fixed();

/**
 * Free's a circular buffer.
 * Should only be called if buffer was created using circ_init
 * @param buffer Buffer to be freed
 */
void circ_free(circ_buffer* buffer);
/**
 * Writes a single item to a circular buffer
 * @param buffer Target circular buffer
 * @param item Item to add
 */
void circ_write(circ_buffer *buffer, uint8_t item);

/**
 * Reads a single item from a circular buffer.
 *
 * Should check is the buffer is not empty before calling this function. If the buffer is empty then the return value
 * is undefined.
 * @todo Maybe make this function blocking or make circ_read_b
 * @param buffer Target circular buffer
 * @return Value read from the buffer
 */
uint8_t circ_read(circ_buffer *buffer);

/**
 * Checks if the buffer is empty
 * @param buffer Target circular buffer
 * @return returns True if the buffer is empty
 */
bool circ_is_empty(const circ_buffer *buffer);

/**
 * Checks if the buffer is full
 * @param buffer Target circular buffer
 * @return returns True if the buffer is full
 */
bool circ_is_full(const circ_buffer *buffer);

#endif /* CIRCULAR_BUFFER_H_ */
