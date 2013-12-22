#ifndef _NP_L1_CHUNKSTACK
#define _NP_L1_CHUNKSTACK

typedef struct _NP_CHUNK_STACK
{
	char* up;
	char* down;
	unsigned int size;
	unsigned int chunk_size;
	unsigned int chunk_count;
}NP_CHUNK_STACK;

typedef int NP_CHUNK_STACK_ID;

void* npMakeChunkStack(void* up,void* down, char* stack_ptr,unsigned int chunk_size,unsigned int chunk_count);
char* npChunkStackGet(NP_CHUNK_STACK* sp,NP_CHUNK_STACK_ID id);
unsigned int  npChunkStackSize(NP_CHUNK_STACK* sp);
void  npChunkStackClear(NP_CHUNK_STACK* sp);

#endif
