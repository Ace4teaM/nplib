#ifndef _RIFF_H
#define _RIFF_H

#include "endian.h"
#include "memory.h"

typedef struct _RIFF{
	char id[4];
	unsigned int size;
}RIFF;

typedef struct _RIFF_HEADER{
	//DATA
	char format[4];
}RIFF_HEADER;

bool riff_read(PTR* mem,RIFF* header);
bool riff_write(PTR* mem,const RIFF* header);

#endif
