#ifndef _NP_L1_FILE
#define _NP_L1_FILE

#include <stdio.h>

int fileWrite(const char* filename,const char* mode,char* begin,char* end);
int fileRead(const char* filename,const char* mode,char* begin,char* end);
int fileCat(FILE* fp,char* begin,char* end);

#endif
