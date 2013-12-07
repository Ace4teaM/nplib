#include <sys1.h>
#include "l2/handle.c"

NP_STACK* _stack=0;

char sys1[SYS1_STACK_SIZE];
NP_HANDLE exit_proc;

int init_sys1()
{
	char* up   = sys1;
	char* down = up+SYS1_STACK_SIZE;
	SYS1_FUNC func;

	/* initialise la pile globale */
	puts("init_sys1: initialise la pile globale");
	_stack = (NP_STACK*)up;
	if(!(up = npMakeStack(up,down,0,-1)))
	{
		NP_RESULT("init_sys1","npMakeStack_failed",1);
		return 0;
	}
	
	/* initialise les handles */
	puts("init_sys1: initialise les handles");
	if(!npInitHandle(SYS1_HMAX,SYS1_HSIZE))
	{
		NP_RESULT("init_sys1","npInitHandle_failed",1);
		return 0;
	}

	/*
		ajoute les procedures
	*/
	puts("init_sys1: ajoute les procedures");

	/* exit() */
	strCopy(func.name, func.name+sizeof(func.name), "exit");
	exit_proc  = npUnlockHandle(NP_HANDLE_NULL,&func,0,sizeof(func));
	printf("exit_proc end\n");
	
	return 1;
}
