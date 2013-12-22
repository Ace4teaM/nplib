#ifndef _NP_L1_INT32
#define _NP_L1_INT32

#include <np.h>

void* npMakeInt32( void* up, void* down, char* data);
void* int32Add(int* self,void* end);
void* int32Sub(int* self,void* end);
void* int32Div(int* self,void* end);
void* int32DivSecure(int* self,void* end);

#endif
