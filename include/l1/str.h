/*
	ASCII string
*/
#ifndef _NP_L1_STR
#define _NP_L1_STR

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

#ifdef GTEST
#include <include\gtest\gtest.h>
#endif

char* str_ltrim( char* up, char* down );
char* str_rtrim( char* up, char* down );
void str_trim( char** up, char** down );
/*
char* strLength( char* up, char* down, size_t* psize );
char* strCopy( char* up, char* down, const char* str );
char* strWriteInteger( char* up, char* down, int data );
const char* strReadInteger( const char* up, const char* down, int* data );
const char* strReadUInteger( const char* up, const char* down, unsigned int* data);
char* strWriteUInteger( char* up, char* down, unsigned int data);
char* strParse(char* begin,char* end,const char* txt,...);*/

#endif