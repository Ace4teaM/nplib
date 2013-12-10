#ifndef _NP_L1_RESOURCE
#define _NP_L1_RESOURCE

#include <np.h>

typedef struct _NP_RESOURCE{
	NP_HANDLE prev;
	NP_HANDLE next;
	ushort size;
	ushort order;
}NP_RESOURCE;


NP_HANDLE npCreateResource(const char* name);

#endif
