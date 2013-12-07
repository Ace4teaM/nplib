#include <l1/int.h>

void* npMakeInt32( void* up, void* down, char* data)
{
	char* self = (char*)up;

	if(self+4 >= (char*)down)
		return 0;

	if(data)
	{
		*self++ = *data++;
		*self++ = *data++;
		*self++ = *data++;
		*self++ = *data++;
	}

	return self;
}

void* int32Add(int* self,void* end)
{
	self[2] = self[0] + self[1];
	return self;
}

void* int32Sub(int* self,void* end)
{
	self[2] = self[0] - self[1];
	return self;
}

void* int32Div(int* self,void* end)
{
	self[2] = self[0] / self[1];
	return self;
}

void* int32DivSecure(int* self,void* end)
{
	if(self[1] == 0)
	{
		return self;
	}
	self[2] = self[0] / self[1];
	return self;
}
