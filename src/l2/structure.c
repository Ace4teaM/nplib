#ifndef _NP_L2_STRUCT
#define _NP_L2_STRUCT

#include <np.h>

typedef struct _NP_HANDLE_STRUCT
{
	int hDescriptor;
	int hData;
}NP_HANDLE_STRUCT;

void* npLockStruct(int handle,void* dst);
int npUnlockStruct(int handle,void* src);

#endif
