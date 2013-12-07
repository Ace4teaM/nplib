#include <stdio.h>
#include <l1/texts.h>

int main()
{
	unsigned char value[]={0x10,0x20,0x40,0x60};
	char name[512];

	size_t data_length,i;

	texts_prints("hello","world");
	texts_printi("time",465122);
	texts_printh("foo",0xff);
	texts_printd("bar",value,sizeof(value));

	if(texts_readname(name,name+sizeof(name)))
	{
		printf("read %s = ",name);
		if(data_length = texts_readvalue(value,value+sizeof(value)))
		{
			i=0;
			while(i<data_length)
			{
				printf(" %.2X",value[i]);
				i++;
			}
		}
	}
	return 0;
}
