#ifndef _NP_L1_MEMORY
#define _NP_L1_MEMORY

#include <np.h>

void* npMakeAlloc(void* up,void* down,uint size);
void* npMakeCopy(void* up,void* down,void* data,uint size);
void* npMakeZero(void* up,void* down,uint size);

#endif