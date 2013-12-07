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

	return 0;
}

void checkpixels()
{
	npSet("x","0");
	npSet("y","0");
	npSet("w","10");
	npForEach(0,1);
	npCheckZero();
}

void make_pixels()
{
	int pixels = npCreateList();
	npInsert(pixels, npCreatePoint(1,0,0));
	npInsert(pixels, npCreatePoint(1,0,0));
	npInsert(pixels, npCreatePoint(1,0,0));
	npInsert(pixels, npCreatePoint(1,0,0));
	npInsert(pixels, npCreatePoint(1,0,0));
	npInsert(pixels, npCreatePoint(1,0,0));
}