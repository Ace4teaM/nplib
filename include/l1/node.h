/*
	Assure la compatibilite des types. les descriptor formate les types de bases numerique et binaire associable au C/C++
*/
#ifndef _NP_L1_NODE
#define _NP_L1_NODE

#include <stddef.h>
#include <stdarg.h>

typedef struct _NODE
{
	int count;
	void* ref[1];
}NODE;

void* nodeMake(void* begin, void* end, int count, void* ref, ...);
void* nodeGetRef( NODE* node, int n );
void* nodeSetRef( NODE* node, int n, void* ref );

#endif
