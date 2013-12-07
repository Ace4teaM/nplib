/*
	Stack
	Simple pile de donnees lineaire LastIn-FirstOut
*/

#include <l1/stack.h>
#include <l1/memory.h>

/*
	Initialise une pile

	Parametres:
		up,down : plage memoire des donnees
		stack   : pointeur sur la pile de donnees a utiliser. Si Zero, la pile est ajouter a la plage memoire
		size    : taille de la pile en bytes

	Retourne:
		Pointeur sur le debut de l'objet suivant. Zero, si la fonction echoue.
*/
void* npMakeStack(void* up,void* down,char* stack,size_t size)
{
	NP_STACK* self = (NP_STACK*)up;

	/* initialise l'en-tete */
	if(!(up = npMakeAlloc(up,down,sizeof(NP_STACK))))
		return 0;
	
	/* alloue le tampon ? */
	if(stack==0)
	{
		/* taille auto ? */
		if(size == (size_t)-1)
		{
			size = (size_t)((char*)down-(char*)up);
			/*printf("%d bytes calculated for stack data\n",size);*/
		}

		/* alloue */
		stack = (char*)up;
		if(!(up = npMakeAlloc(up,down,size)))
			return 0;
	}
	
	self->pos  = stack;
	self->up   = stack;
	self->down = stack + size;

	NP_LOG("%d bytes (%p:%p) %d",size,self->up,self->down,(size_t)(self->down-self->up));

	return up;
}

/*
	Reinitialise la pile a zero
*/
void npStackReset(NP_STACK* stack)
{
	stack->pos = stack->up;
}

/*
	Taille de la pile
*/
uint npStackSize(NP_STACK* stack)
{
	return (uint)(stack->down - stack->up);
}

/*
	Taille de l'espace libre
*/
uint npStackFreeSize(NP_STACK* stack)
{
	return (uint)(stack->down - stack->pos);
}

/*
	Taille de l'espace occupe
*/
uint npStackUsedSize(NP_STACK* stack)
{
	return (uint)(stack->pos-stack->up);
}

/*
	Alloue la pile
*/
void* npStackReserve(NP_STACK* stack,size_t size)
{
	char* ptr = stack->pos;

	/* espace suffisant pour l'allocation ? */
	if(stack->pos + size > stack->down)
		return 0;

	/* deplace le curseur */
	stack->pos += size;
	
	NP_LOG("%d bytes\n",size);

	return ptr;
}

/*
	Alloue la pile et copie les donnees
	Retourne:
		Pointeur sur les donnees. Si 0, espace insuffisant.
*/
void* npStackPush(NP_STACK* stack,const void* _data,size_t size)
{
	const char* data = (const char*)_data;
	char* base_ptr = stack->pos;
	
	/* espace suffisant pour l'allocation ? */
	if(stack->pos + size > stack->down){
		/*printf("stack_push: insuffisant space (%d) free=%d\n",size,stack_space(stack));*/
		return 0;
	}
	
	/* deplace le curseur et copie les donnees */
	while(size--)
		*stack->pos++ = *data++;
	
	NP_LOG("%d bytes\n",size);

	return base_ptr;
}

/*
	Dealloue la pile
	Retourne:
		Nouvelle position de l'allocation.
*/
void* npStackPop(NP_STACK* stack,void* data)
{
	char* ptr = (char*)data;

	/* 'data' fait bien partie de la pile ? */
	if(ptr < stack->up || ptr > stack->pos){
/*		printf("stack_pop: invalid pointer range (%p)\n",ptr);*/
		return 0;
	}
	
	/* deplace le curseur */
	stack->pos = ptr;

	return stack->pos;
}

/*
	Retourne la position de l'allocation en cours
*/
char* npStackPos(NP_STACK* stack)
{
	return stack->pos;
}
