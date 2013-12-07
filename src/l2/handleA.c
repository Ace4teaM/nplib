#include <l2/handle.h>

extern NP_STACK* _stack;

NP_CHUNK_STACK* _handle_data; /* blocks de donnees des handles */
NP_HANDLE* _handles; /* liste des handles (chaque handle pointe sur l'handle suivant */
NP_HANDLE _free_handle = NP_HANDLE_NULL; /* handle qui liste les blocks libres */
char* _lockbuffer = 0;

int npInitHandle()
{
	void *up,*down;
	int i;

	/* initialise dans la pile globale */
	up   = npStackPos(_stack);
	down = (char*)up + npStackFreeSize(_stack);

	/* initialise la pile des donnees */
	_handle_data = (NP_CHUNK_STACK*)up;
	if(!(up = npMakeChunkStack(up,down, 0,HANDLE_CHUNK_SIZE,HANDLE_COUNT)))
		return 0;
	
	/*
		initialise la pile des handles
		chaque handle pointe le prochain qui le lie
		(handle_id == data_id)
	*/
	_handles = (NP_HANDLE*)up;
	if(!(up = npMakeZero(up,down, sizeof(NP_HANDLE)*(HANDLE_COUNT))))
		return 0;
	
	/*
		initialise la plage de verrouillage
	*/
	_lockbuffer = (char*)up;
	if(!(up = npMakeZero(up,down, LOCK_SIZE)))
		return 0;
	
	/*
		lie les handles
	*/
	_free_handle = 0;
	for(i=0;i<HANDLE_COUNT-1;i++)
	{
		_handles[i] = i+1;
	}
	_handles[i] = NP_HANDLE_NULL;/*dernier*/

	return 1;
}

NP_HANDLE npCreateHandle(void* data,uint size)
{
	NP_HANDLE cur,first;
	uint required_chunk = size/HANDLE_CHUNK_SIZE;
	if(required_chunk*HANDLE_CHUNK_SIZE < size)/*arrondie*/
		required_chunk++;
	
	/* aucun chunk libre ? */
	if( !required_chunk )
	{
		NP_RESULT("npCreateHandle","zero_size",1);
		return NP_HANDLE_NULL;
	}

	/* aucun chunk libre ? */
	if( _free_handle == NP_HANDLE_NULL )
	{
		NP_RESULT("npCreateHandle","free_handle",1);
		return NP_HANDLE_NULL;
	}

	/* compte le nombre de block disponibles */
	first = cur = _free_handle;
	while(cur != NP_HANDLE_NULL && required_chunk){
		required_chunk--;
		if(required_chunk)
			cur = _handles[cur];/*suivant*/
	}
	/* pas assez de block ? */
	if(required_chunk)
	{
		NP_RESULT("npCreateHandle","required_chunk",1);
		return NP_HANDLE_NULL;
	}

	/* ok, isole les deux listes */
	_free_handle = _handles[cur];/*nouveau block de debut de liste */
	_handles[cur] = NP_HANDLE_NULL;/*termine la liste de la nouvelle allocation */
	/*printf("free=%d\n",_free_handle);
	printf("first=%d\n",first);*/

	/* copie les donnees */
	if(data!=0)
		npUnlockHandle(first,data,0,size);

	return first;
}

/*
	retourne l'handle des blocks libres
*/
NP_HANDLE npFreeHandle()
{
	return _free_handle;
}

/*
	verifie le rang de valeur d'un handle
*/
int npIsHandle(NP_HANDLE handle)
{
	return (handle<0 || handle>=HANDLE_COUNT) ? 0 : 1;
}

/*
	retourne la taille d'un handle en byte
*/
uint npHandleSize(NP_HANDLE handle)
{
	uint count;
	NP_HANDLE next;
	
	if(!npIsHandle(handle))
	{	/*printf("%d\n",handle);*/
		NP_RESULT("npHandleSize","invalid_handle",1);
		return 0;
	}

	count = 1;
	next = _handles[handle];
	while(next != NP_HANDLE_NULL){
		next = _handles[next];
		count++;
	}
	return count*HANDLE_CHUNK_SIZE;
}

/*
	lit les donnees d'un handle
*/
void* npLockHandle(NP_HANDLE handle,uint offset,uint size)
{
	NP_HANDLE cur=handle;
	int i;
	char* dst=_lockbuffer;
	char* src;

	/* verifie l'handle */
	if(!npIsHandle(handle))
	{
		NP_RESULT("npLockHandle","invalid_handle",1);
		return 0;
	}

	/* verifie la taille */
	if(size>LOCK_SIZE)
	{
		NP_RESULT("npLockHandle","lock_buffer_too_small",1);
		return 0;
	}
	
	/* verifie la taille */
	if(size==0)
	{
		size = LOCK_SIZE;/* tout */
	}
	
	/*printf("npLockHandle copie %d bytes max\n",size);*/

	/* copie les donnees */
	while(cur != NP_HANDLE_NULL && size)
	{
		src = npChunkStackGet(_handle_data,cur);
		/*copie*/
		i=0;
		while(size && i<HANDLE_CHUNK_SIZE)
		{
			*dst++ = *src++;
			i++;
			size--;
		}
		/*printf("npLockHandle block %d, rest=%d bytes max\n",cur,size);*/
		/*suivant*/
		cur = _handles[cur];
	}
	
	return _lockbuffer;
}

/*
	ecrit les donnees d'un handle
*/
NP_HANDLE npUnlockHandle(NP_HANDLE handle,void* data,uint offset,uint size)
{
	NP_HANDLE cur=handle;
	int i;
	char* dst;
	char* src=(char*)((data==0) ? _lockbuffer : data);

	/* verifie l'handle */
	if(!npIsHandle(handle))
	{
		NP_RESULT("npLockHandle","invalid_handle",1);
		return 0;
	}

	/* verifie la taille 
	if(data==0 && size>LOCK_SIZE)
	{
		NP_RESULT("npLockHandle","lock_buffer_too_small",1);
		return 0;
	}*/
	
	/* verifie la taille */
	if(size==0)
	{
		NP_RESULT("npUnlockHandle","no_size",1);
		return 0;
	}

	/*printf("npUnlockHandle copie %d bytes\n",size);*/

	/* copie les donnees */
	while(cur != NP_HANDLE_NULL && size)
	{
		dst = npChunkStackGet(_handle_data,cur);
		/*copie*/
		i=0;
		while(size && i<HANDLE_CHUNK_SIZE)
		{
			*dst++ = *src++;
			i++;
			size--;
		}
		/*printf("npUnlockHandle block %d, rest=%d bytes\n",cur,size);*/
		/*suivant*/
		cur = _handles[cur];
	}
	
	return handle;
}
