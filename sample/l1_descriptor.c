/*
	Test l'ecriture de donnees portables

*/

#include <stdio.h>
#include <np.h>
#include <l1/desc.h>
#include <l1/file.h>
#include <math.h>
#include <float.h>

void* make_descriptor(void* cur,void* end);
void* read_descriptor(void* cur,void* end);

int main()
{
   double x, y, d;

	char data[200];
	void* begin = data;
	void* end = data+sizeof(data);
	void* eod;

	/* ecrit */
	eod = make_descriptor(begin,end);
	if(!fileWrite("test.desc",begin,eod))
		return 0;

	/* lit */
	if(fileRead("test.desc",begin,end))
		eod = read_descriptor(begin,end);

	
	/* extraction d'un nombre a virgule */
   x = 14.876;
   y = modf(x, &d);

   printf("x = %lf\n", x);
   printf("Integral part = %d\n", (int)d);
   printf("Fractional part = %d\n", (int)y);
   printf("value = %d, %2x %2x %2x %2x %2x %2x %2x %2x\n", sizeof(y), ((unsigned char*)&y)[0], ((unsigned char*)&y)[1], ((unsigned char*)&y)[2], ((unsigned char*)&y)[3], ((unsigned char*)&y)[4], ((unsigned char*)&y)[5], ((unsigned char*)&y)[6], ((unsigned char*)&y)[7]);
	return 0;
}

void* make_descriptor(void* cur,void* end)
{
	const unsigned char color[] = {255,128,64};
	int value = -45792;/*0x7FFFFFFF;*/
	cur = descWriteText(cur,end,"my descriptor");

	// int
	cur = descWriteByte(cur,end,DESC_INT);
	cur = descWriteSize(cur,end,sizeof(int));
	cur = descWriteInteger(cur,end,(char*)&value,sizeof(value));
	
	// raw
	cur = descWriteByte(cur,end,DESC_RAW);
	cur = descWriteSize(cur,end,sizeof(color));
	cur = descWriteRaw(cur,end,color,sizeof(color));

	// text
	cur = descWriteByte(cur,end,DESC_TEXT);
	cur = descWriteText(cur,end,"hello world");
	
	// cint
	cur = descWriteByte(cur,end,DESC_CINT);
	cur = strWriteInteger(cur,end,value);
	
	return cur;
}

void* read_descriptor(void* cur,void* end)
{
	size_t size;
	unsigned char type;
	int int_value;
	char text[128];
	unsigned char raw[128];
	size_t i;

	cur = descReadText(cur,end,text,sizeof(text));
	puts(text);
	
	// int
	cur = descReadByte(cur,end,&type);
	cur = descReadSize(cur,end,&size);
	cur = descReadInteger(cur,end,(char*)&int_value,sizeof(int_value));
	printf("read int %d %d %d\n",type,size,int_value);
	
	// raw
	cur = descReadByte(cur,end,&type);
	cur = descReadSize(cur,end,&size);
	cur = descReadRaw(cur,end,raw,size);
	printf("read raw %d %d: ",type,size);
	i=0;
	while(i<size)
	{
		printf("0x%2x,",raw[i]);
		i++;
	}
	printf("\n");

	// text
	cur = descReadByte(cur,end,&type);
	size = (size_t)cur;
	cur = descReadText(cur,end,text,sizeof(text));
	size = (size_t)cur - size;
	printf("read text %d %d %s\n",type,size,text);

	// cint
	cur = descReadByte(cur,end,&type);
	//cur = descReadSize(cur,end,&size);
	cur = strReadInteger(cur,end,&int_value/*,size*/);
	printf("read cint %d %d\n",type,int_value,size);
	
	return cur;
}
