#ifndef _ENDIAN_H
#define _ENDIAN_H

#include "memory.h"

/* Endianness */
#define LITTLE_ENDIAN 0
#define BIG_ENDIAN    1
#define SPEC_ENDIAN 2 /* non supporter pour le moment */
#define ENDIAN (((int)1)&0x1 ? LITTLE_ENDIAN : BIG_ENDIAN)/*test le systeme actuel*/

/* test le systeme actuel */
static const short ENDIAN_TEST = 1;
#if (ENDIAN_TEST&0x0001)
#define IS_LITTLE_ENDIAN
#elif (ENDIAN_TEST&0x1000)
#define IS_BIG_ENDIAN
#else
#define IS_SPEC_ENDIAN
#endif

// bytes to type
int btoi(PTR* dat);
short btos(PTR* dat);
long btol(PTR* dat);

// type to bytes
bool itob(PTR* dat, int val);
bool stob(PTR* dat, short val);
bool ltob(PTR* dat, long val);

// bytes to type
int btoi(const char* dat);
short btos(const char* dat);
long btol(const char* dat);

// type to bytes
char* itob(char* dat, int val);
char* stob(char* dat, short val);
char* ltob(char* dat, long val);

#endif
