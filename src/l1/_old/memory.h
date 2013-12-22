#ifndef _NP_L1_MEMORY
#define _NP_L1_MEMORY

void* npMakeAlloc(void* up,void* down,unsigned int size);
void* npMakeCopy(void* up,void* down,void* data,unsigned int size);
void* npMakeZero(void* up,void* down,unsigned int size);

#endif