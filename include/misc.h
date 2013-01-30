/**
 * \file misc.h
 *
 * \author Jared Lewis (jared at bodekerscientific dot com)
 * \date 14/01/2013
 *
 * Header file containing misc function calls. This header also abstracts the microcontroller specifics
 * from the developer.
 */

#ifndef MISC_H_
#define MISC_H_

#include <stdint.h>

//Checks for complier compiles with C99
#if __STDC_VERSION__ >= 199901L
	/* C99 code */
	#define C99
#endif

/**
 * Defines bool in a standard way
 */
#ifdef C99
	#include <stdbool.h>
#else
	typedef enum { false, true } bool;
#endif

#define NULL 0

/**
 * Useful defines for manipulating bits
 */

/// Zero a single bit of a register without affecting the rest
#define BIT_RESET(reg, bitNum) 	reg &= ~(1<<bitNum)
/// Set a single bit of a register
#define BIT_SET(reg, bitNum)	reg |= (1<<bitNum)
/// Left shift by a number of bits
#define BIT(bitNum)				(1<<bitNum)

#endif /* MISC_H_ */
