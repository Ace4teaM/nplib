#include <l1/memory.h>
#include <l1/chunkstack.h>

/*
	ChunkStack Lib

	Manage un tampon en fragment de zone
*/

/*
	Make
*/

void* npMakeChunkStack(void* up,void* down, char* stack_ptr,unsigned int chunk_size,unsigned int chunk_count)
{
	NP_CHUNK_STACK* self;
	uint stack_size = chunk_size*chunk_count;

	/* initialise l'en-tete */
	self = (NP_CHUNK_STACK*)up;
	if(!(up = npMakeAlloc(up,down,sizeof(NP_CHUNK_STACK))))
		return 0;
	
	/* alloue le tampon ? */
	if(stack_ptr==0)
	{
		stack_ptr = up;
		if(!(up = npMakeAlloc(up,down,stack_size)))
			return 0;
	}

	/* initialise la strucutre */
	self->up          = stack_ptr;
	self->down        = self->up + stack_size;
	self->size        = stack_size;
	self->chunk_size  = chunk_size;
	self->chunk_count = chunk_count;
	
	return up;
}

/*
	efface la pile
*/
void npChunkStackClear(NP_CHUNK_STACK* sp)
{
	char* ptr = sp->up;
	unsigned int size = sp->size;
	while(size--)
		*ptr++ = 0;
}

/*
	taille de la pile sans l'en-tete
*/
unsigned int npChunkStackSize(NP_CHUNK_STACK* sp)
{
	return sp->size;
}

/*
	obtient un pointeur de donnees
*/
char* npChunkStackGet(NP_CHUNK_STACK* sp,NP_CHUNK_STACK_ID id)
{
	char* ptr = sp->up + (id * sp->chunk_size);
	if(ptr+sp->chunk_size > sp->down)
		return 0;
	return ptr;
}
