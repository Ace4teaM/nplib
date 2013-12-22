#ifndef _MEMORY
#define _MEMORY

typedef struct _PTR{
	char *up,*down,*ptr;
}PTR;

char* bread(char* up,char* down,void* _data,unsigned int size);
char* bwrite(char* up,char* down,const void* _data,unsigned int size);

#endif