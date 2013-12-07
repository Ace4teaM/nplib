/*
	Assure la compatibilite des types. les descriptor formate les types de bases numerique et binaire associable au C/C++
*/
#ifndef _NP_L1_DESC
#define _NP_L1_DESC

#include <stddef.h>
#include <stdarg.h>

/*
	Endianness
*/
#define ENDIAN_LITTLE 0
#define ENDIAN_BIG    1
#define ENDIAN_MIDDLE 2 /* non supporter pour le moment */
#ifndef ENDIAN_THIS
#define ENDIAN_THIS   (((int)1)&0x1 ? ENDIAN_LITTLE : ENDIAN_BIG)/*test le systeme actuel*/
#endif

/*
	portable descriptor
	Decrit un element portable
*/
#define DESC_INT     0x01 /*number*/
#define DESC_RAW     0x02
#define DESC_TEXT    0x03
#define DESC_CINT    0x04
#define DESC_COMPLEX 0x05 /*-1~1*/
#define DESC_REAL    0x06 /*x.x*/
#define DESC_DEGREE  0x07 /*0-360*/
#define DESC_RADIAN  DESC_COMPLEX
#define DESC_NUMBER  DESC_INT /*number*/
#define DESC_END     0xff /*number*/

typedef struct{
	char* name;
	unsigned char type;
	size_t size;
}DESC;

void* descMake(void* begin, void* end, ...);
void* descWriteIdentifier( void* up, void* down, const char* text );
void* descWriteText( void* up, void* down, const char* text );
void* descWriteRaw( void* up, void* down, const unsigned char* raw, size_t size );
void* descWriteByte( void* up, void* down, unsigned char byte );
void* descWriteSize(void* up, void* down,size_t size);
void* descWriteInteger( void* up, void* down, char* value, size_t size);
void* descWriteInt( void* up, void* down, int value);
void* descWriteUInt( void* up, void* down, unsigned int value);
void* descReadIdentifier( void* up, void* down, char* text, size_t size );
void* descReadText( void* up, void* down, char* text, size_t size );
void* descReadByte( void* up, void* down, unsigned char* byte );
void* descReadRaw( void* up, void* down, unsigned char* out, size_t size );
void* descReadSize(void* up, void* down,size_t* psize);
void* descReadInteger( void* up, void* down, char* value, size_t size);
void* descReadInt( void* up, void* down, int* value);
void* descReadUInt( void* up, void* down, unsigned int* value);

void* descWriteNumber( void* up, void* down, int value);
void* descReadNumber( void* up, void* down, int* pvalue);

void* descNumberToFloat( void* up, void* down, float* pvalue);
void* ldescFloatToNumber( void* up, void* down, float value, int precision);
void* descNumberToInt( void* up, void* down, int* pvalue);
void* ldescIntToNumber( void* up, void* down, int value);

/*
	local descriptor
	Decrit un element de l'implementation locale
*/

#define LDESC_INT    1
#define LDESC_RAW    2
#define LDESC_TEXT   3 /* asciiz */
#define LDESC_FLOAT  4
#define LDESC_DOUBLE 5

typedef struct{
	unsigned char type;
	const char* name;
}LDESC;

void* descWriteStruct(void* up,void* down,LDESC* desc,int count,void* _structData);
int descReadStruct(void* up,void* down,LDESC* ldesc,int count,void* _structData);
/*
void* ldescFloatToComplex( void* up, void* down, float value);
void* ldescFloatToReal( void* up, void* down, float value);
void* ldescDoubleToComplex( void* up, void* down, float value);
void* ldescDoubleToReal( void* up, void* down, double value);
void* ldescIntToNumber( void* up, void* down, int value);
void* ldescUIntToNumber( void* up, void* down, unsigned int value);*/

#endif
