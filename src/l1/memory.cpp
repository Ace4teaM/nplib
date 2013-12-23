#include "memory.h"


/**
	@brief Ecrit (copie) des données
*/
bool bwrite(PTR* mem,const void* _data,unsigned int size)
{
	const char* data = (const char*)_data;
	if(mem->ptr+size > mem->down)
	{
//		NP_RESULT("npMakeZero","allocation_limit",1);
		return 0;
	}

	while(size--)
		*mem->ptr++ = *data++;

	return true;
}

/**
	@brief Lit (copie) des données
*/
bool bread(PTR* mem,void* _data,unsigned int size)
{
	char* data = (char*)_data;
	if(mem->ptr+size > mem->down)
	{
//		NP_RESULT("npMakeZero","allocation_limit",1);
		return 0;
	}

	while(size--)
		*data++ = *mem->ptr++;

	return true;
}

/**
	@brief Rembobine le pointeur
*/
PTR* brewind(PTR* mem){
	mem->ptr = mem->up;
	return mem;
}

/**
	@brief Initialise le pointeur
*/
PTR* bptr(PTR* mem,void* dat,int size){
	mem->up = (char*)dat;
	mem->down = mem->up+size;
	mem->up = mem->up;
	return mem;
}