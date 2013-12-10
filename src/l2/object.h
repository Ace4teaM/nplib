#ifndef _NP_L2_OBJECT
#define _NP_L2_OBJECT

#include <np.h>

typedef struct _NP_OBJECT_STRUCT{
	int att_count;
}NP_OBJECT_STRUCT;

typedef struct _NP_OBJECT_ATTRIBUTE_STRUCT{
	char name[64-sizeof(int)];
	int hStructData;
}NP_OBJECT_ATTRIBUTE_STRUCT;

NP_HANDLE npCreateObject();

#endif
