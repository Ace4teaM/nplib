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
