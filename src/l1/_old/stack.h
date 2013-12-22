#ifndef _NP_L1_STACK
#define _NP_L1_STACK

#include <stddef.h>
#include "memory.h"

/*
	STACK element
*/

typedef struct _NP_STACK
{
	char* pos;  /* position de l'allocation */
	char* up;   /* debut du tampon */
	char* down; /* fin du tampon */
}NP_STACK;

void* npMakeStack(void* up,void* down,char* stack,size_t size);
void  npStackReset(NP_STACK* stack);
unsigned int  npStackSize(NP_STACK* stack);
unsigned int  npStackFreeSize(NP_STACK* stack);
unsigned int  npStackUsedSize(NP_STACK* stack);
void* npStackReserve(NP_STACK* stack,size_t size);
void* npStackPush(NP_STACK* stack,const void* data,size_t size);
void* npStackPop(NP_STACK* stack,void* data);
char* npStackPos(NP_STACK* stack);

#endif
