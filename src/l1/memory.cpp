#include "memory.h"


/**
	@brief Ecrit (copie) des données
    @param mem Tampon mémoire
    @return true
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
    @param mem Tampon mémoire
    @return true
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
    @param mem Tampon mémoire
    @return Tampon
*/
PTR* brewind(PTR* mem){
	mem->ptr = mem->up;
	return mem;
}

/**
	@brief Initialise le pointeur
    @param mem Tampon mémoire
    @return Tampon
*/
PTR* bptr(PTR* mem,void* dat,int size){
	mem->up = (char*)dat;
	mem->down = mem->up+size;
    mem->ptr = mem->up;
	return mem;
}

/**
    @brief Retourne l'offset du pointeur
    @param mem Tampon mémoire
    @return Taille en bytes (down - ptr)
*/
unsigned int boffset(PTR* mem){
    return (unsigned int)(mem->ptr - mem->up);
}

/**
    @brief Retourne la taille du tampon
    @param mem Tampon mémoire
    @return Taille en bytes (down - up)
*/
unsigned int bsize(PTR* mem){
    return (unsigned int)(mem->down - mem->up);
}
