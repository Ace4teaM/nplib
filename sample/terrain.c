#include <stdio.h>
#include <np.h>
#include <l2/handle.h>

char mem[1024*10];

void print_free();
void make_string();

int main()
{
	/* initialise NP */
	if(!npInit(mem,mem+sizeof(mem)) || !npInitHandle())
		return 1;
	
	/* affiche l'etat de la memoire */
	print_free();

	/* alloue un handle */
	make_string();
	
	/* affiche l'etat de la memoire */
	print_free();

	return 0;
}

void print_free()
{
	if(npFreeHandle() == NP_HANDLE_NULL)
		printf("No free handles data\n");
	else
		printf("Free handles data = %d\n",npHandleSize(npFreeHandle()));
}

void make_string()
{
	NP_HANDLE string = npCreateHandle("hello world",11);

	printf("string(%d) %d bytes = %s\n", string, npHandleSize(string), npLockHandle(string,0,0));
}