#ifdef NP_DEBUG

#include <windows.h>
#include <np.h>
#include "../include/wincsl.h"

HANDLE log_hConsole=NULL;

void winlogInit()
{
	AllocConsole();
	log_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//np callback
	npLogOut = winlogConsoleOut;
}

void winlogFree()
{
	FreeConsole();
	log_hConsole = NULL;

	//np callback default
	npLogOut = npLogToFile;
}

char* winlogConsoleOut(char* buf,char* end)
{
	size_t size=0;
	strLength(buf,end,&size);
	WriteConsole(log_hConsole,(const char*)buf,size,NULL,NULL);
	return buf;
}

#endif
