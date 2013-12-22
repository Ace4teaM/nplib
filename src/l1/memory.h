#ifndef _MEMORY
#define _MEMORY

typedef struct _PTR{
	char *up,*down,*ptr;
}PTR;

bool bread(PTR* mem,void* _data,unsigned int size);
bool bwrite(PTR* mem,const void* _data,unsigned int size);
PTR* brewind(PTR* mem);
PTR* bptr(PTR* mem,void* dat,int size);

#endif