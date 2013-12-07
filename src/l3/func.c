#include <l3/func.h>

char* npAdd(char* o1,char* o2)
{
	int h1 = npGetHandle(o1);
	int h2 = npGetHandle(o2);
	int n  = npAdd(h1,h2);
	return npGetHandleName(n);
}

char* npSub(char* o1,char* o2)
{
	return 0;
}

char* npDiv(char* o1,char* o2)
{
	return 0;
}
