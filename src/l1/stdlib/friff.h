#ifndef _STDIO_RIFF_H
#define _STDIO_RIFF_H

#include "../riff.h"
#include "fendian.h"
#include <stdio.h>

bool riff_fwrite(FILE* fp,const RIFF* header);
bool riff_fread(FILE* fp,RIFF* header);

#endif
