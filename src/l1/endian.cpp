#include "endian.h"

/**
	@brief Bytes (little endian) to Integer type
	@param dat Input buffer
	@return Value
*/
int btoi(PTR* dat){
	int val=0;
	int size=sizeof(int);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+=sizeof(long);
	while(size--)
	{
		*--iptr = *dat->ptr++;
	}
#else
	char* iptr=(char*)&val;
	while(size)
	{
		*iptr++ = *dat->ptr++;
		size--;
	}
#endif
	return val;
}

/**
	@brief Bytes (little endian) to Long type
	@param dat Input buffer
	@return Value
*/
long btol(PTR* dat){
	long val=0;
	int size=sizeof(long);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+=sizeof(long);
	while(size--)
	{
		*--iptr = *dat->ptr++;
	}
#else
	char* iptr=(char*)&val;
	while(size)
	{
		*iptr++ = *dat->ptr++;
		size--;
	}
#endif
	return val;
}

/**
	@brief Bytes (little endian) to Short type
	@param dat Input buffer
	@return Value
*/
short btos(PTR* dat){
	short val=0;
	int size=sizeof(short);
#ifdef IS_BIG_ENDIAN
	char* iptr=((char*)&val)+=sizeof(short);
	while(size--)
	{
		*--iptr = *dat->ptr++;
	}
#else
	char* iptr=(char*)&val;
	while(size)
	{
		*iptr++ = *dat->ptr++;
		size--;
	}
#endif
	return val;
}

/**
	@brief Integer type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
bool itob(PTR* dat, int val){
#ifdef IS_BIG_ENDIAN
	dat->ptr+=sizeof(int);
	char* ptr=dat->ptr;
	char* iptr=(char*)&val;
	while(ptr>=dat)
	{
		*--ptr = *iptr++;
	}
#else
	int size = sizeof(int);
	char* iptr=(char*)&val;
	while(size)
	{
		*dat->ptr++ = *iptr++;
		size--;
	}
#endif
	return true;
}

/**
	@brief Short type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
bool stob(PTR* dat, short val){
#ifdef IS_BIG_ENDIAN
	dat->ptr+=sizeof(short);
	char* ptr=dat->ptr;
	char* iptr=(char*)&val;
	while(ptr>=dat)
	{
		*--ptr = *iptr++;
	}
#else
	int size = sizeof(short);
	char* iptr=(char*)&val;
	while(size)
	{
		*dat->ptr++ = *iptr++;
		size--;
	}
#endif
	return true;
}

/**
	@brief Long type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
bool ltob(PTR* dat, long val){
#ifdef IS_BIG_ENDIAN
	dat->ptr+=sizeof(long);
	char* ptr=dat->ptr;
	char* iptr=(char*)&val;
	while(ptr>=dat)
	{
		*--ptr = *iptr++;
	}
#else
	int size = sizeof(long);
	char* iptr=(char*)&val;
	while(size)
	{
		*dat->ptr++ = *iptr++;
		size--;
	}
#endif
	return true;
}
/**
	@brief Bytes (little endian) to Integer type
	@param dat Input buffer
	@return Value
*/
int btoi(const char* dat){
	int val=0;
#ifdef IS_BIG_ENDIAN
	const char* ptr=dat;
	char* iptr=((char*)&val)+=sizeof(int);
	while(ptr>=dat)
	{
		*--iptr = *ptr++;
	}
#else
	int size = sizeof(int);
	const char* ptr=dat;
	char* iptr=(char*)&val;
	while(size)
	{
		*iptr++ = *ptr++;
		size--;
	}
#endif
	return val;
}

/**
	@brief Bytes (little endian) to Long type
	@param dat Input buffer
	@return Value
*/
long btol(const char* dat){
	long val=0;
#ifdef IS_BIG_ENDIAN
	const char* ptr=dat;
	char* iptr=((char*)&val)+=sizeof(long);
	while(ptr>=dat)
	{
		*--iptr = *ptr++;
	}
#else
	int size = sizeof(long);
	const char* ptr=dat;
	char* iptr=(char*)&val;
	while(size)
	{
		*iptr++ = *ptr++;
		size--;
	}
#endif
	return val;
}

/**
	@brief Bytes (little endian) to Short type
	@param dat Input buffer
	@return Value
*/
short btos(const char* dat){
	short val=0;
#ifdef IS_BIG_ENDIAN
	const char* ptr=dat;
	char* iptr=((char*)&val)+=sizeof(short);
	while(ptr>=dat)
	{
		*--iptr = *ptr++;
	}
#else
	int size = sizeof(short);
	const char* ptr=dat;
	char* iptr=(char*)&val;
	while(size)
	{
		*iptr++ = *ptr++;
		size--;
	}
#endif
	return val;
}

/**
	@brief Integer type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
char* itob(char* dat, int val){
#ifdef IS_BIG_ENDIAN
	char* ptr=dat+=sizeof(int);
	char* iptr=(char*)&val;
	while(ptr>=dat)
	{
		*--ptr = *iptr++;
	}
#else
	int size = sizeof(int);
	char* ptr=dat;
	char* iptr=(char*)&val;
	while(size)
	{
		*ptr++ = *iptr++;
		size--;
	}
#endif
	return dat;
}

/**
	@brief Short type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
char* stob(char* dat, short val){
#ifdef IS_BIG_ENDIAN
	char* ptr=dat+=sizeof(short);
	char* iptr=(char*)&val;
	while(ptr>=dat)
	{
		*--ptr = *iptr++;
	}
#else
	int size = sizeof(short);
	char* ptr=dat;
	char* iptr=(char*)&val;
	while(size)
	{
		*ptr++ = *iptr++;
		size--;
	}
#endif
	return dat;
}

/**
	@brief Long type to bytes (little endian)
	@param dat Output buffer
	@param val Input value
	@return dat pointer
*/
char* ltob(char* dat, long val){
#ifdef IS_BIG_ENDIAN
	char* ptr=dat+=sizeof(long);
	char* iptr=(char*)&val;
	while(ptr>=dat)
	{
		*--ptr = *iptr++;
	}
#else
	int size = sizeof(long);
	char* ptr=dat;
	char* iptr=(char*)&val;
	while(size)
	{
		*ptr++ = *iptr++;
		size--;
	}
#endif
	return dat;
}
/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST

TEST(endian, tob) {
    char bytes[50];
	PTR ptr={bytes,bytes+sizeof(bytes),bytes};

    stob(&ptr,456);
    itob(&ptr,789545);
    ltob(&ptr,25646);
	brewind(&ptr);

    ASSERT_EQ(456, btos(&ptr)) << "short";
    ASSERT_EQ(789545, btoi(&ptr)) << "int";
    ASSERT_EQ(25646, btol(&ptr)) << "long";
}

#endif