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

char* riff_read(char* up, char* down,RIFF* header);
char* riff_write(char* up, char* down,const RIFF* header);

#endif
