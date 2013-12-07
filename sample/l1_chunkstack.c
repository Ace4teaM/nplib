#include <stdio.h>
#include <l1/chunkstack.h>

char data[200];
NP_CHUNK_STACK* stack = (NP_CHUNK_STACK*)data;

int main()
{
	if(!npMakeChunkStack(data,data+sizeof(data),0,10,10))
		return 1;

	printf("size = %d\n",npChunkStackSize(stack));
	printf("count = %d (%d bytes)\n",stack->chunk_count,stack->chunk_size);
	
	return 0;
}
