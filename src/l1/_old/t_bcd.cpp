/*
	Binary coded numbers (binaire-octal-decimal-hexadecimale)

	Chiffre Bits    Chiffre Bits
		0   0000        5   0101
		1   0001        6   0110
		2   0010        7   0111
		3   0011        8   1000
		4   0100        9   1001
		A   1010        B   1011
		C   1100        D   1101
		E   1011        F   1111
*/
#include "t_bcd.h"

void* npMakeBCD( void* up, void* down, char* ascii, size_t size)
{
	char a,b;
	char* self = (char*)up;
	while(self < (char*)down && size)
	{
		a = (*ascii) - '0';
		if(size)
		{
			size--;
			ascii++;
			b = (*ascii) - '0';
		}
		else
			b=0;
		
		*self = (((b)&0xf) << 4)| ((a)&0xf);
	
		ascii++;
		self++;
		size--;
	}
	return self;
}


void* npBCNAdd( void* up, void* down, char* dst, char* a, char* b)
{
	return 0;
}

void* npBCNToInt( void* up, void* down, char* dst, char* a, char* b)
{
	return 0;
}
