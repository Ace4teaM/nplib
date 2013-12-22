#include "memory.h"


/**
	@brief Ecrit (copie) des données
*/
char* bwrite(char* up,char* down,const void* _data,unsigned int size)
{
	const char* data = (const char*)_data;
	if(up+size > down)
	{
//		NP_RESULT("npMakeZero","allocation_limit",1);
		return 0;
	}

	while(size--)
		*up++ = *data++;

	return up;
}

/**
	@brief Lit (copie) des données
*/
char* bread(char* up,char* down,void* _data,unsigned int size)
{
	char* data = (char*)_data;
	if(up+size > down)
	{
//		NP_RESULT("npMakeZero","allocation_limit",1);
		return 0;
	}

	while(size--)
		*data++ = *up++;

	return up;
}
