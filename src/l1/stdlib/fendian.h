#ifndef _STDIO_FENDIAN_H
#define _STDIO_FENDIAN_H

#include "../endian.h"
#include <stdio.h>

/**
	@brief File (little endian) to Short type
	@param dat Input buffer
	@return Value
*/
short ftos(FILE* fp);

/**
	@brief File (little endian) to Integer type
	@param dat Input buffer
	@return Value
*/
int ftoi(FILE* fp);

/**
	@brief File (little endian) to Long type
	@param dat Input buffer
	@return Value
*/
long ftol(FILE* fp);

/**
	@brief Short type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
FILE* stof(FILE* fp, short val);

/**
	@brief Integer type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
FILE* itof(FILE* fp, int val);

/**
	@brief Long type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
FILE* ltof(FILE* fp, long val);

#endif
