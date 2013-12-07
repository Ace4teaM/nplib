#include <stdio.h>
#include <l1/desc.h>
//#include <l1/file.h>

typedef struct
{
	int width;
	int height;
	char* dataformat;
}iImage;

typedef struct
{
	int bpp;
	char* pixels;
}iBitmapImage;

int main()
{
	char data[200];
	void* desc,*struct1;
	void* cur = data;
	void* end = data+sizeof(data);
	size_t desc_size;
	
	/* fabrique le descripteur */
	desc = cur;
	cur = descMake(cur,end,
		"x",DESC_INT,sizeof(int),
		"y",DESC_INT,sizeof(int),
		"z",DESC_INT,sizeof(int)
	);
	desc_size = (size_t)cur - (size_t)desc;
	if(cur==0)
		return 1;

	printf("size = %d\n",descSize(desc));
	
	/* ecrit une structure */
	cur = descWriteStruct(cur,end,desc,desc_size,10,20,30);
	if(cur==0)
		return 1;

	/* ecrit une structure */
	struct1 = cur;
	cur = descWriteStruct(cur,end,desc,desc_size,10,20,30);
	if(cur==0)
		return 1;

	return 0;
}
