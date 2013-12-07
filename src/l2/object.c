#include <l2/handle.h>

NP_HANDLE npCreateObject()
{
	NP_HANDLE obj;
	NP_OBJECT_STRUCT* pobj;

	obj = npCreateHandle(0,sizeof(NP_OBJECT_STRUCT));

	pobj = npLockHandle(obj,0,sizeof(NP_OBJECT_STRUCT));
	pobj->att_count = 0;
	npUnlockHandle(obj,pobj,0,sizeof(NP_OBJECT_STRUCT));

	return obj;
}

void test(){
	struct
	{
		char* version = "1.3.22";
		char* name = "test;";
		int bin=10;
	}data;

	npUnlockStruct(hSysProg,&data,0,sizeof(NP_OBJECT_STRUCT));
}
