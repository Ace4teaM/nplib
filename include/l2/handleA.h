#ifndef _NP_L1_HANDLE
#define _NP_L1_HANDLE

#include <np.h>
#include <l1/chunkstack.h>

#define HANDLE_CHUNK_SIZE 64
#define HANDLE_COUNT      10
#define LOCK_SIZE         (HANDLE_COUNT*HANDLE_CHUNK_SIZE)

#define NP_HANDLE NP_CHUNK_STACK_ID
#define NP_HANDLE_NULL (-1)

typedef struct _NP_HANDLE_STRUCT{
	NP_CHUNK_STACK_ID data_id;
	NP_HANDLE next_handle;
}NP_HANDLE_STRUCT;

typedef struct _NP_HANDLE32{
	uint next : 16;
	uint size : 16;
}NP_HANDLE32;

int       npInitHandle();
NP_HANDLE npFreeHandle();
NP_HANDLE npCreateHandle(void* data,uint size);
uint      npHandleSize(NP_HANDLE handle);
void*     npLockHandle(NP_HANDLE handle,uint offset,uint size);
NP_HANDLE npUnlockHandle(NP_HANDLE handle,void* data,uint offset,uint size);
int       npIsHandle(NP_HANDLE handle);

#endif
