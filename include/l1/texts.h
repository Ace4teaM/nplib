#ifndef _NP_L1_TEXTS
#define _NP_L1_TEXTS

#ifdef WIN32
#include <io.h>
#define write _write
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>

// read formats
#define texts_ischar(c) (((c)>0x1f && (c)!=0x20 && (c)<0x7f) ? 1 : 0)
#define texts_ishex(c) ((((c)>=0x30 && (c)<=0x39) || ((c)>=0x41 && (c)<=0x46) || ((c)>=0x61 && (c)<=0x66)) ? 1 : 0)
size_t texts_readname(char* name, char* end);
int texts_readwhitespace();
size_t texts_readvalue(char* value,const char* end);
size_t texts_readbytevalue(char* value,const char* end);

// print formats
void texts_prints(const char* name, const char* string);
void texts_printi(const char* name, int value);
void texts_printh(const char* name, int value);
void texts_printd(const char* name, const unsigned char* data, size_t size);

#endif
