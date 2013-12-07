#include <stdio.h>
#include <np.h>
#include <l2/handle.h>

char mem[1024*10];

void init();

int main()
{
	NP_HANDLE ostruct;
	OSTRUCT ostruct;

	/* init */
	init();
	
	/* cree la structure */
	hstruct = npCreateStruct(
		"np version",
		"version",
		1,
		10
	);
	
	/* modifie */
	ostruct.upper = 1;
	ostruct.lower = 11;
	npUnlockStruct(hstruct,&ostruct,0,sizeof(ostruct));

	return 0;
}

void init()
{
	/* initialise NP */
	if(!npInit(mem,mem+sizeof(mem)) || !npInitHandle())
		exit(1);
}

struct
{
	void* next;
	void* prev;
}l0;

struct
{
	int next;
	int prev;
}l1;

struct
{
	char* next;
	char* prev;
}l2;

#ifdef NP_HANDLE
#undef NP_HANDLE
#endif
#define NP_HANDLE void*

void testl0()
{
	NP_HANDLE h1 = npCreateHandle(0,sizeof(IDENTIFIER));
	NP_HANDLE h2 = npCreateHandle(0,sizeof(IDENTIFIER));
	NP_HANDLE h3 = npCreateHandle(0,sizeof(IDENTIFIER));
}

