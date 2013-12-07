#include <stdio.h>


//structure local
typedef struct{
	int time;
	char ip[4];
	char name[256];
}ETH;
/*
void* textlen( char* up, char* down, size_t* size );
void* npread( void* up, void* down, void* data, size_t data_size, DESC* desc, size_t desc_size );
void* npwrite( void* up, void* down, void* data, size_t data_size, DESC* desc, size_t desc_size );
void* npwritetext( void* up, void* down, char* text, size_t size );
void* npwriteraw( void* up, void* down, char* raw, size_t size );
void* npwriteint( void* up, void* down, char* data, size_t size );
unsigned char* bytes_to_size(unsigned char* bytes,unsigned int* psize);
unsigned char size_to_bytes(unsigned int size,unsigned int* bytes_count);
*/
void* npreaddesc( void* up, void* down, const char** name, unsigned char* type, size_t* size );
void* npwritedesc( void* up, void* down, const char* name, unsigned char type, size_t size );
int fput( void* up, void* down, FILE* fp );
void* fget( void* up, void* down, FILE* fp );

//descripteur local
DESC _ETH_DESC[] = {
	{"time",INT,sizeof(int)},
	{"ip",RAW,4},
	{"name",TEXT,256}
};

int main(int argc,const char* argv[])
{
	char buf[2048];
	void* end = buf;
	ETH eth;
	FILE* fp;

	//ecrit la structure 
	if(fp = fopen("test.np","wb"))
	{
		// write ethernet interface structure
		eth.time = 0x01020304;
		eth.ip[0] = 127;
		eth.ip[1] = 0;
		eth.ip[2] = 0;
		eth.ip[3] = 1;
		sprintf(eth.name,"default");

		end = npwrite( buf, buf+sizeof(buf), &eth, sizeof(eth), _ETH_DESC, sizeof(_ETH_DESC) );
		if(end != 0)
		{
			if(fput( buf, end, fp ) == 0)
				puts("fput error");
		}
		else puts("npwrite error");

		fclose(fp);
	}
	else puts("fopen error");

	//lit
	/*if(fp = fopen("test.np","rb"))
	{
		end = fget(buf, buf+sizeof(buf), fp);

		if(end)
		{
			npread( buf, end, &eth, sizeof(eth), _ETH_DESC, 0 );

			printf("ethernet interface v4:\n");
			printf("time: %d\n",eth.time);
			printf("ip  : %d.%d.%d.%d\n",eth.ip[0],eth.ip[1],eth.ip[2],eth.ip[3]);
			printf("name: %s\n",eth.name);
		}
		
		fclose(fp);
	}*/


	return 0;
}

void* npget( void* up, void* down, const char* data, size_t data_size, DESC* desc, size_t desc_size )
{
	size_t desc_count = desc_size/sizeof(DESC);
	size_t i;
	char* self=(char*)up;
	DESC cur_desc;
	
	/* lit les descripteurs et leurs donnees */
	i=0;
	while( (self<(char*)down) )
	{
		/* lit le descripteur */
		if((self = (char*)npreaddesc( self, down, &cur_desc.name, &cur_desc.type, &cur_desc.size ))==0)
			return 0;
		
		i=0;
		while(i < desc_count && strcmp(cur_desc.name,desc[i].name)!=0)
			i++;
		if(i==desc_count)/* inconnue */
			return 0;
		
		if(cur_desc.size>desc[i].size)
			return 0;
		
		if(cur_desc.type!=desc[i].type)
			return 0;

	}

	return 0;
}

//ecrit une structure portable
void* npwrite( void* up, void* down, void* pin, size_t data_size, DESC* desc, size_t desc_size )
{
	size_t desc_count = desc_size/sizeof(DESC);
	size_t i,wsize;
	char* self=(char*)up;
	char* data=(char*)pin;

	/* ecrit les descripteurs et leurs donnees */
	i=0;
	while( i < desc_count )
	{
		if(desc[i].type == TEXT)
		{
			if(textlen(data,data+desc[i].size,&wsize) == 0)
			{
				printf("npwrite: textlen\n");
				return 0;
			}
		}
		else if((wsize = desc[i].size)==0)
		{
			printf("npwrite: empty size\n");
			return 0;
		}

		/* ecrit le descripteur */
		if((self = (char*)npwritedesc(self, down, desc[i].name, desc[i].type, wsize)) == 0)
		{
			printf("npwrite: npwritedesc\n");
			return 0;
		}

		/* ecrit les donnees */
		printf("write %s (%d bytes)\n",desc[i].name,wsize);
		switch(desc[i].type)
		{
			case TEXT:
				self = (char*)npwritetext(self,down,data,wsize);
				break;
			case INT:
				self = (char*)npwriteint(self,down,data,wsize);
				break;
			default:
				self = (char*)npwriteraw(self,down,data,wsize);
				break;
		}
		
		/* erreur ? */
		if(self == 0)
		{
			printf("npwrite: npwrite*\n");
			return 0;
		}

		/* ajuste le pointeur sur la structure */
		data += desc[i].size;
		
		//fin de section
		*self++ = 0x0;

		/* descripteur suivant */
		i++;
	}
	
	return self;
}

//lit le contenu d'un fichier
void* fget( void* up, void* down, FILE* fp )
{
	char* self = (char*)up;
	int c;

	while((c = fgetc(fp)) != EOF && (self<(char*)down))
		*self++ = (char)c;

	return self;
}

//lit le contenu d'un fichier
int fput( void* up, void* down, FILE* fp )
{
	size_t size = (size_t)((char*)down-(char*)up);
	if(fwrite(up,size,1,fp) != 1)
		return 0;

	return 1;
}


//test un caractere
#define ischar(c) (((c)>0x1f && (c)!=0x20 && (c)<0x7f) ? 1 : 0)

//lit un descripteur
void* npreaddesc( void* up, void* down, const char** name, unsigned char* type, size_t* size )
{
	char* self = (char*)up;

	/* nom */
	*name = self;
	while((self < (char*)down) && ischar(*self))
		*self++;
	if(*self!=0)
		return 0;
	*self++ = 0;

	/* taille */
	self = (char*)bytes_to_size((unsigned char*)self,size);

	/* type */
	*type++ = *self++;

	return self;
}

//ecrit un descripteur
void* npwritedesc( void* up, void* down, const char* name, unsigned char type, size_t size )
{
	char* self = (char*)up;
	unsigned int byte_count;
	unsigned char byte_rest;

	/* nom */
	while((self < (char*)down) && ischar(*name))
		*self++ = *name++;
	if(*name!=0)
		return 0;
	*self++ = 0;

	/* taille */
	byte_rest = size_to_bytes(size,&byte_count);
	while((self < (char*)down) && (byte_count--))
		*self++ = 0xff;
	if(self==(char*)down)
		return 0;
	*self++ = byte_rest;

	/* type */
	*self++ = type;

	return self;
}
