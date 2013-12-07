#include <stdio.h>
#include <l1/desc.h>

char data[200];

int main()
{
	if(!npMakeDesc(data,data+sizeof(data),
		"x",DESCRIPTOR_TYPE_INT,sizeof(int),
		"y",DESCRIPTOR_TYPE_INT,sizeof(int),
		"z",DESCRIPTOR_TYPE_INT,sizeof(int)
	))
		return 1;

	/*printf("size = %d\n",npDescElement(data)->type);*/
	
	return 0;
}

