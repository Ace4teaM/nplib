/*
	ASCII string
*/
#ifndef _NP_L1_LIST
#define _NP_L1_LIST

#include <np.h>

typedef struct{
	LIST_ITEM* next;
}LIST_ITEM;

typedef struct{
	int max;
	LIST_ITEM* item;
}LIST;

void* listMake( char* up, char* down, int max );
int listInsert( LIST* down, int pos );
int listRemove( LIST* down, int pos );
int listCount( LIST* down, int first );

#endif

