#ifndef _NP_L1_INT
#define _NP_L1_INT

#include <np.h>

/* Endianness */
#define NP_LITTLE_ENDIAN 0
#define NP_BIG_ENDIAN    1
#define NP_MIDDLE_ENDIAN 2 /* non supporter pour le moment */
#define NP_THIS_ENDIAN (((int)1)&0x1 ? NP_LITTLE_ENDIAN : NP_BIG_ENDIAN)/*test le systeme actuel*/

void* npReadInt( void* up, void* down, char* data, size_t size);
void* npMakeInt( void* up, void* down, char* data, size_t size);
void* npStoreInt( void* up, void* down, char* data, size_t size);
void* npLoadInt( void* up, void* down, char* data, size_t size);

#endif
