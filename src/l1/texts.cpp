#include "texts.h"

/*
	print formats
*/

void texts_prints(const char* name, const char* string)
{
	fwrite(name,strlen(name),1,stdout);
	fwrite(" \"",2,1,stdout);
	fwrite(string,strlen(string),1,stdout);
	fwrite("\"\n",2,1,stdout);
}

void texts_printi(const char* name, int value)
{
	char buf[11];/*32bits max*/
	sprintf(buf,"%d",value);
	fwrite(name,strlen(name),1,stdout);
	fwrite(" ",1,1,stdout);
	fwrite(buf,strlen(buf),1,stdout);

	fwrite("\n",1,1,stdout);
}

void texts_printh(const char* name, int value)
{
	char buf[12];/*32bits max*/
	sprintf(buf,"h%X",value);
	fwrite(name,strlen(name),1,stdout);
	fwrite(" ",1,1,stdout);
	fwrite(buf,strlen(buf),1,stdout);

	fwrite("\n",1,1,stdout);
}

void texts_printd(const char* name, const char* data, size_t size)
{
	char buf[4];/*2bytes + 1 espace*/
	fwrite(name,strlen(name),1,stdout);
	fwrite(" {",2,1,stdout);

	while(size--)
	{
		sprintf(buf,"%.2X",(int)(*data));
		fwrite(buf,strlen(buf),1,stdout);
		data++;
	}

	fwrite("}\n",2,1,stdout);
}

/*
	read formats
*/

size_t texts_readname(char* name, const char* end)
{
	int c=texts_readwhitespace();
	size_t size=0;
	while((c != EOF) && (name != end))
	{
		if(!texts_ischar(c))
		{
			*name++ = 0;
			return size;
		}

		*name++ = (char)c;

		c=getc(stdin);
		size++;
	}

	return size;
}

size_t texts_readvalue(char* value,const char* end)
{
	int c=texts_readwhitespace();
	size_t size=0;

	switch(c)
	{
	case '{':
		//puts("read data...");
		return texts_readbytevalue(value,end);
	/*case '"':
		return texts_readstringvalue(value,end);
	case 'h':
		return texts_readhexavalue(value,end);
	case 'o':
		return texts_readoctalvalue(value,end);*/
	}

	return 0;
}

size_t texts_readbytevalue(char* value,const char* end)
{
	int c=texts_readwhitespace();
	size_t size=0;
	char byte[3];
	unsigned int _value;
	
	while(c != EOF && value<end)
	{
		/* premier */
		if(!texts_ishex(c))
			return size;
		byte[0] = (char)c;
		//printf("c1=%c",c);
		/* deuxieme */
		c=getc(stdin);
		if(!texts_ishex(c))
			return size;
		byte[1] = (char)c;
		//printf("c2=%c",c);
		/* fin */
		byte[2] = 0;

		sscanf(byte,"%2x",&_value);

		//printf("read: %s (%d)",byte,(int)(*value));

		*value++ = (unsigned char)_value;
		size++;

		c=getc(stdin);
	}

	return size;
}

int texts_readwhitespace()
{
	int c;
	while((c=getc(stdin)) != EOF)
	{
		if(texts_ischar(c))
			return c;
	}

	return c;
}

