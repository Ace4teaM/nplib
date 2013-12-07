/*
	Handle Data list.

	Implemente les routines globales d'allocation dynamique de la memoire.
	L'Handle est un indice obtenu par npCreateHandle, il identifie la mémoire alloue.

	Globales:
		header       : pointeur sur la structure d'en-tete
		_free_handle : handle de la memoire libre.
*/
#include <l2/handle.h>

extern NP_STACK* _stack;

NP_HANDLE_HEADER* header = 0;
NP_HANDLE         _free_handle = NP_HANDLE_NULL;

size_t npGetHandleLockBufferSize()
{
	return header->data_size;
}

void* npGetHandleLockBuffer()
{
	return header->lock_data;
}

/*
	Alloue est initialise la memoire

	Parametres:
		handle_count : nombre d'handle allouable
		handle_size  : taille d'un handle

	Retourne:
		1 en cas de succes, 0 en cas d'erreur.
*/
ushort npInitHandle(ushort handle_count,ushort handle_size)
{
	void *up,*down;
	int i;

	/* utilise la pile globale */
	up   = npStackPos(_stack);
	down = (char*)up + npStackFreeSize(_stack);
	
	/*
		initialise l'en-tete
	*/
	header = (NP_HANDLE_HEADER*)up;
	if(!(up = npMakeAlloc(up,down, sizeof(NP_HANDLE_HEADER))))
		return 0;
	header->chunk_count= handle_count;
	header->chunk_size = handle_size;
	header->data_size  = handle_count*handle_size;
	
	/*
		initialise la pile des handles
	*/
	header->index = (NP_HANDLE_INDICE*)up;
	if(!(up = npMakeAlloc(up,down, handle_count*sizeof(NP_HANDLE_INDICE))))
		return 0;
	
	/*
		initialise la pile de donnees
	*/
	header->data = (char*)up;
	if(!(up = npMakeAlloc(up,down, header->data_size)))
		return 0;
	
	/*
		initialise la tampon de verouillage
	*/
	header->lock_data = (char*)up;
	if(!(up = npMakeAlloc(up,down, header->data_size)))
		return 0;
	
	/*
		initialise l'handle des donnees libres
	*/
	_free_handle = 0;
	for(i=0;i<header->chunk_count-1;i++)
	{
		header->index[i].next  = i+1;
		header->index[i].prev  = i-1;/*NP_HANDLE_NULL si -1*/
		header->index[i].size  = 0;
		header->index[i].order = 0;
	}
	/*dernier*/
	header->index[i].next  = NP_HANDLE_NULL;
	header->index[i].prev  = i-1;
	header->index[i].size  = 0;
	header->index[i].order = 0;
	/*premier*/
	header->index[0].size=header->data_size;

	return 1;
}

/*
	Alloue un handle

	Parametres:
		data : donnees de l'allocation. Si 0, ignore.
		size : taille desire en bytes

	Retourne:
		handle, NP_HANDLE_NULL en cas d'echec.
*/
NP_HANDLE npCreateHandle(void* data,size_t size)
{
	NP_HANDLE last,first;
	size_t size_rest;
	
	/* aucun block libre ? */
	if( size > header->data_size )
	{
		NP_RESULT("npCreateHandle","size_limit_exceded",1);
		return NP_HANDLE_NULL;
	}

	/* aucun block libre ? */
	if( _free_handle == NP_HANDLE_NULL )
	{
		NP_RESULT("npCreateHandle","free_handle",1);
		return NP_HANDLE_NULL;
	}
	
	/* obtient le dernier block */
	first = last = _free_handle;
	size_rest=size;
	while(last != NP_HANDLE_NULL && ((int)size_rest-(int)header->chunk_size)>=header->chunk_size)
	{
		size_rest -= header->chunk_size;
		last = header->index[last].next;
	}
	if(last==NP_HANDLE_NULL)
	{
		NP_RESULT("npCreateHandle","unavailable_required_chunk_number",1);
		return NP_HANDLE_NULL;
	}

	/* isole la liste libre */
	_free_handle = header->index[last].next;
	header->index[_free_handle].size=header->index[first].size-size;
	/* isole la nouvelle liste */
	header->index[last].next = NP_HANDLE_NULL;/*termine*/
	header->index[first].size = size;

	printf("npCreateHandle: alloc=%d handle(#%d->#%d)\n",header->index[first].size,first,last);
	printf("npCreateHandle: rest=%d handle(#%d)\n",header->index[_free_handle].size,_free_handle);

	/* copie les donnees */
	if(data!=0)
		npUnlockHandle(first,data,0,size);

	return first;
}

/*
	retourne l'handle de la memoire libre
*/
NP_HANDLE npFreeHandle()
{
	return _free_handle;
}

/*
	verifie un handle
*/
int npIsHandle(NP_HANDLE handle)
{
	return (handle==NP_HANDLE_NULL || handle>=header->chunk_count) ? 0 : 1;
}

/*
	retourne la taille d'un handle en bytes
*/
size_t npHandleSize(NP_HANDLE handle)
{
	size_t size = 0;
	
	if(!npIsHandle(handle))
	{
		NP_RESULT("npHandleSize","invalid_handle",1);
		return 0;
	}

	return (size_t)header->index[handle].size;
}

/*
	lit les donnees d'un handle
*/
void* npLockHandle(NP_HANDLE handle,void* data,size_t offset,size_t size)
{
	NP_HANDLE cur=handle;
	ushort i;
	char* dst=(data==0) ? header->lock_data : (char*)data;
	char* dst_base=dst;
	char* src;
	NP_HANDLE_INDICE* phi;

	/* verifie l'handle */
	if(!npIsHandle(handle))
	{
		NP_RESULT("npLockHandle","invalid_handle",1);
		return 0;
	}
	
	/* obtient le pointeur */
	phi = &header->index[handle];

	/* verifie la taille */
	if(data==0 && size>header->data_size)
	{
		NP_RESULT("npLockHandle","lock_buffer_too_small",1);
		return 0;
	}
	
	/* verifie la taille */
	if(offset+size>phi->size || offset>=phi->size)
	{
		NP_RESULT("npLockHandle","invalid_lock_size",1);
		return 0;
	}
	
	/* verifie la taille */
	if(size==0)
	{
		size = phi->size-offset;/* tout */
	}
	
	/**/printf("npLockHandle %d:%d bytes\n",offset,size);
	
	/* saute l'offset et copie les donnees */
	while(cur != NP_HANDLE_NULL && size)
	{
		src = header->data + (header->chunk_size * cur);
		i=0;
		if(offset)
		{
			if(offset>=header->chunk_size)
			{
				/*suivant*/
				cur = header->index[cur].next;
				offset-=header->chunk_size;
				continue;
			}
			else
			{
				src += offset;
				i=offset;
				offset=0;
			}
		}
		/*copie*/
		while(size && i<header->chunk_size)
		{
			*dst++ = *src++;
			i++;
			size--;
		}
		/*suivant*/
		cur = header->index[cur].next;
	}
	if(size)
	{
		NP_RESULT("npLockHandle","partial_data_locked",1);
		return 0;
	}

	return dst_base;
}

/*
	ecrit les donnees d'un handle
*/
NP_HANDLE npUnlockHandle(NP_HANDLE handle,void* data,size_t offset,size_t size)
{
	NP_HANDLE cur;
	ushort i;
	char* dst;
	char* src=(char*)((data==0) ? header->lock_data : data);
	NP_HANDLE_INDICE* phi;
	
	/* nouvelles donnees ? */
	if(handle==NP_HANDLE_NULL)
	{
		handle=npCreateHandle(0,size);
	}

	/* verifie l'handle */
	if(!npIsHandle(handle))
	{
		NP_RESULT("npUnlockHandle","invalid_handle",1);
		return 0;
	}
	
	/* obtient le pointeur */
	phi = &header->index[handle];

	/* verifie la taille */
	if(data==0 && size>header->data_size)
	{
		NP_RESULT("npUnlockHandle","lock_buffer_too_small",1);
		return 0;
	}
	
	/* verifie la taille */
	if(size==0)
	{
		NP_RESULT("npUnlockHandle","no_size",1);
		return 0;
	}

	/* verifie la taille */
	if(offset+size>phi->size || offset>=phi->size)
	{
		NP_RESULT("npUnlockHandle","invalid_lock_size",1);
		return 0;
	}
	
	printf("npUnlockHandle #%d -> %d:%d bytes\n",handle,offset,size);

	/* saute l'offset et copie les donnees */
	cur=handle;
	while(cur != NP_HANDLE_NULL && size)
	{
		dst = header->data + (header->chunk_size * cur);
		i=0;
		if(offset)
		{
			if(offset>=header->chunk_size)
			{
				//suivant
				cur = header->index[cur].next;
				offset-=header->chunk_size;
				continue;
			}
			else
			{
				dst += offset;
				i=offset;
				offset=0;
			}
		}
		//copie
		while(size && i<header->chunk_size)
		{
			*dst++ = *src++;
			i++;
			size--;
		}
		//suivant
		cur = header->index[cur].next;
	}
	if(size)
	{
		NP_RESULT("npUnlockHandle","partial_data_locked",1);
		return 0;
	}
	printf("npUnlockHandle end\n");
	return handle;
}
