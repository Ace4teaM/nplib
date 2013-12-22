#include "endian.h"

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
	long val;
    char bytes[8];

    stob(bytes,456);
    val = (long)btos(bytes);
    ASSERT_EQ(456, val);
	
    itob(bytes,789545);
    val = (long)btoi(bytes);
    ASSERT_EQ(789545, val);
	
    ltob(bytes,25646);
    val = btol(bytes);
    ASSERT_EQ(25646, val);
}

#endif