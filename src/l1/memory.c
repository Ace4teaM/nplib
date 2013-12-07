#include <np.h>
#include <l1/memory.h>

/*
	Alloue la plage de donnees
*/
void* npMakeAlloc(void* up,void* down,uint size)
{
	char* pos = ((char*)up)+size;

	if(pos > (char*)down)
	{
		NP_LOG("npMakeAlloc: (failed) %i/%i bytes (%p)\n",size,(int)((char*)down-(char*)up),pos);
		NP_RESULT("npMakeAlloc","allocation_limit",1);
		return 0;
	}
	NP_LOG("npMakeAlloc: %i/%i bytes (%p)\n",size,(size_t)((char*)down-(char*)up),pos);

	return pos;
}

/*
	Alloue et copie la plage de donnees
*/
void* npMakeCopy(void* up,void* down,void* data,uint size)
{
	char* src = (char*)data;
	char* dst = (char*)up;

	if(dst+size > (char*)down)
	{
		NP_RESULT("npMakeCopy","allocation_limit",1);
		return 0;
	}

	while(size--)
		*dst++ = *src++;

	return dst;
}

/*
	Alloue la plage de donnees a zero
*/
void* npMakeZero(void* up,void* down,uint size)
{
	char* dst = (char*)up;

	if(dst+size > (char*)down)
	{
		NP_RESULT("npMakeZero","allocation_limit",1);
		return 0;
	}

	while(size--)
		*dst++ = 0;

	return dst;
}
