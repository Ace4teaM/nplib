#include "..\endian.h"
#include "fendian.h"

/**
	@brief File (little endian) to Short type
	@param dat Input buffer
	@return Value
*/
short ftos(FILE* fp){
	short val=0;
	int size=sizeof(short);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+sizeof(short);
	while(size--)
	{
		*--iptr = (char)fgetc( fp );
	}
#else
	char* iptr=((char*)&val);
	while(size--)
	{
		*iptr++ = (char)fgetc( fp );
	}
#endif
	return val;
}

/**
	@brief File (little endian) to Integer type
	@param dat Input buffer
	@return Value
*/
int ftoi(FILE* fp){
	int val=0;
	int size=sizeof(int);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+sizeof(int);
	while(size--)
	{
		*--iptr = (char)fgetc( fp );
	}
#else
	char* iptr=((char*)&val);
	while(size--)
	{
		*iptr++ = (char)fgetc( fp );
	}
#endif
	return val;
}

/**
	@brief File (little endian) to Long type
	@param dat Input buffer
	@return Value
*/
long ftol(FILE* fp){
	long val=0;
	int size=sizeof(long);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+sizeof(long);
	while(size--)
	{
		*--iptr = (char)fgetc( fp );
	}
#else
	char* iptr=((char*)&val);
	while(size--)
	{
		*iptr++ = (char)fgetc( fp );
	}
#endif
	return val;
}

/**
	@brief Short type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
FILE* stof(FILE* fp, short val){
	int size=sizeof(short);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+sizeof(short);
	while(size--)
	{
		fputc((int)*--iptr,fp);
	}
#else
	char* iptr=((char*)&val);
	while(size--)
	{
		fputc((int)*iptr++,fp);
	}
#endif
	return fp;
}

/**
	@brief Integer type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
FILE* itof(FILE* fp, int val){
	int size=sizeof(int);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+sizeof(int);
	while(size--)
	{
		fputc((int)*--iptr,fp);
	}
#else
	char* iptr=((char*)&val);
	while(size--)
	{
		fputc((int)*iptr++,fp);
	}
#endif
	return fp;
}

/**
	@brief Long type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
FILE* ltof(FILE* fp, long val){
	int size=sizeof(long);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+sizeof(long);
	while(size--)
	{
		fputc((int)*--iptr,fp);
	}
#else
	char* iptr=((char*)&val);
	while(size--)
	{
		fputc((int)*iptr++,fp);
	}
#endif
	return fp;
}

