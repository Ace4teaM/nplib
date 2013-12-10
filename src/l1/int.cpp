#include "int.h"

void* npMakeInt( void* up, void* down, char* data, size_t size)
{
	char* self = (char*)up;

	if(self+size >= (char*)down)
		return 0;

	switch(NP_THIS_ENDIAN)
	{
		case NP_LITTLE_ENDIAN:
			while(size)
			{
				*self++ = *data++;
				size--;
			}
			break;

		case NP_BIG_ENDIAN:
			data+=size-1;
			while(size)
			{
				*self++ = *data--;
				size--;
			}
			break;

		case NP_MIDDLE_ENDIAN:
			return 0;
	}

	return self;
}


void* npReadInt( void* up, void* down, char* data, size_t size)
{
	char* self = (char*)up;

	switch(NP_THIS_ENDIAN)
	{
		case NP_LITTLE_ENDIAN:
			while(size && self<(char*)down)
			{
				*data++ = *self++;
				size--;
			}
			break;

		case NP_BIG_ENDIAN:
			self += size-1;
			while(size && self<(char*)down)
			{
				*data++ = *self--;
				size--;
			}
			break;

		case NP_MIDDLE_ENDIAN:
			return 0;
	}

	if(size)
		return 0;

	return ((char*)up)+size;
}
