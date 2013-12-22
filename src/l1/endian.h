#ifndef _ENDIAN_H
#define _ENDIAN_H

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
/*
// file bytes to type
int ftoi(FILE* fp);
short ftos(FILE* fp);
long ftol(FILE* fp);

// type to file bytes 
FILE* ftoi(FILE* fp, int val);
FILE* ftos(FILE* fp, short val);
FILE* ftol(FILE* fp, long val);
*/
// bytes to type
int btoi(const char* dat);
short btos(const char* dat);
long btol(const char* dat);

// type to bytes
char* itob(char* dat, int val);
char* stob(char* dat, short val);
char* ltob(char* dat, long val);

#endif
