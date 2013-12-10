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
#ifndef _NP_L1_T_BCD
#define _NP_L1_T_BCD

#include <stddef.h>

typedef struct _T_BCN
{
	unsigned char a : 4;
	unsigned char b : 4;
}T_BCN;

void* npMakeBCD( void* up, void* down, char* ascii, size_t size);
void* npBCNAdd( void* up, void* down, char* dst, char* a, char* b);
void* npBCNToInt( void* up, void* down, char* dst, char* a, char* b);

#endif