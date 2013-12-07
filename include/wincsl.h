#ifndef _WINCSL
#define _WINCSL

#ifdef NP_DEBUG

#include "np.h"

#ifdef __cplusplus
extern "C" {
#endif

extern HANDLE log_hConsole;

void winlogInit();
char* winlogConsoleOut(char* buf,char* end);
void winlogFree();

#ifdef __cplusplus
}
#endif

#endif

#endif
