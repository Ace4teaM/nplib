#include <l1/node.h>

void* nodeMake(void* begin, void* end, int count, void* ref, ...)
{
	NODE* node = (NODE*)begin;
	va_list list;
	int i;

	char* next = (char*)begin + sizeof(NODE) + (sizeof(void*)*(count-1));

	if(next>=(char*)end)
		return 0;

	node->count = count;

	va_start(list, end );
	
	/* lit les references */
	for(i=0;i<count;i++)
	{
		node->ref[i] = va_arg(list, void*);
	}
	va_end(list);
	
	return next;
}

void* nodeGetRef( NODE* node, int n )
{
	if(n<0 || n>=node->count)
		return 0;

	return node->ref[n];
}

void* nodeSetRef( NODE* node, int n, void* ref )
{
	if(n<0 || n>=node->count)
		return 0;

	return (node->ref[n] = ref);
}
