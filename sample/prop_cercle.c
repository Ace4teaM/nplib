
/*
	Test l'ecriture de donnees portables

*/

#include <sys1.h>

/*
	longeur de la portion d'un angle (degree) sur un cercle

	(angle->degree/360.0) * circle->length

int circleAngleLength(int circle_length, int angle_degree)
{
	int result = clone(circle_length);
	int _360   = clone(circle_length);
	decimale(_360,"360");
	div(result,angle_degree,_360);
	mul(result,result,circle_length);
	return result;
}

typedef struct
{
	unsigned char data[4];
}INT32_T;

typedef struct
{
	unsigned char data[8];
}INT64_T;

typedef struct
{
	char name[64];
	int hFuncList;
	int hDataList;
}TYPELIST;

typedef struct
{
	char name[64];
	void* call;
}TYPEFUNC;

typedef struct
{
	void* call;
	void* in;
	void* out;
}CALL;

int Div(int result, int a, int b)
{
	TYPEFUNC* func;
	size_t size;
	
	// obtient le typelist

	// recherche la fonction
	size = npHandleSize(func->hFuncList);
	func = (TYPEFUNC*)npLockHandle(func->hFuncList,0,size);

	while( (strCmp(func->name,"div")!=0) && size)
	{
		size -= sizeof(TYPEFUNC);
	}
	if(!size)
		return 0;

	npLock(b);

	strCopy();
	
	npUnlock(result);
	return result;
}*/
NP_HANDLE makeInt(const char* value);

int main()
{
	int circle_length, angle_degree;
	int value=10;
	if(!init_sys1())
		return 0;
	
	circle_length = makeInt("01");
	angle_degree  = makeInt("02");

	/*circle_length = npCreateHandle(0,4);
	angle_degree  = npCreateHandle(0,4);
	
	value=10;
	npUnlockHandle(circle_length,&value,0,sizeof(value));
	value=20;
	npUnlockHandle(angle_degree,&value,0,sizeof(value));*/

	printf("h:%d, %d bytes = %d\n", circle_length, npHandleSize(circle_length), *(int*)npLockHandle(circle_length,0,0,0));
	printf("h:%d, %d bytes = %d\n", angle_degree, npHandleSize(angle_degree), *(int*)npLockHandle(angle_degree,0,0,0));
/*	int circle_length = make(int_t);
	int angle_degree  = make(int_t);
	set(circle_length,"10");
	set(circle_length,"10");

	int angle_length = circleAngleLength(circle_length, angle_degree);*/
}

NP_HANDLE makeInt(const char* value)
{
	NP_HANDLE handle;

	printf("npGetHandleLockBuffer:%p->%p\n", value, strReadInteger(value,value+3,(int*)npGetHandleLockBuffer()));

	if((handle = npUnlockHandle(NP_HANDLE_NULL,0,0,sizeof(int)))==NP_HANDLE_NULL)
		return NP_HANDLE_NULL;

	return handle;
}
