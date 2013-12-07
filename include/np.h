#ifndef _NP
#define _NP

#include <stdlib.h> /* types */
#include <stdio.h> /* debug printf,puts */

#ifdef __cplusplus
extern "C" {
#endif

/*
-----------------------------------------------------------------------------------------------
 Types
-----------------------------------------------------------------------------------------------
*/

//typedef struct _b8{ unsigned char bytes[1]; }b8;
//typedef struct _b16{ unsigned char bytes[2]; }b16;

// Types bits (32bits)
#ifndef _U8_T
#define _U8_T
typedef unsigned char		u8;
#endif
#ifndef _S8_T
#define _S8_T
typedef signed char			s8;
#endif
#ifndef _U16_T
#define _U16_T
typedef unsigned short		u16;
#endif
#ifndef _S16_T
#define _S16_T
typedef signed short		s16;
#endif
#ifndef _U32_T
#define _U32_T
typedef unsigned int		u32;
#endif
#ifndef _S32_T
#define _S32_T
typedef signed int			s32;
#endif

// Types courts
#ifndef _UCHAR_T
#define _UCHAR_T
typedef unsigned char		uchar;
#endif
#ifndef _USHORT_T
#define _USHORT_T
typedef unsigned short		ushort;
#endif
#ifndef _UINT_T
#define _UINT_T
typedef unsigned int		uint;
#endif
#ifndef _SCHAR_T
#define _SCHAR_T
typedef signed char			schar;
#endif
#ifndef _SSHORT_T
#define _SSHORT_T
typedef signed short		sshort;
#endif
#ifndef _SINT_T
#define _SINT_T
typedef signed int			sint;
#endif

// Methods
typedef char* (*NP_LOG_FUNC)(char*,char*);

/*
-----------------------------------------------------------------------------------------------
 Definitions globales
-----------------------------------------------------------------------------------------------
*/

// Bit utiles
#define np_getbit(data,offset)			((data>>offset)&1)
#define np_getnbit(data,offset,size)	((data>>offset)&size)
#define np_clrbit(data,offset)			(((data>>offset)&1)?(data ^= (1<<offset)):(0))
#define np_setbit(data,offset)			((data) |= (1<<(offset)))
#define np_setnbit(data,value,offset)	((data) |= (value<<(offset)))
#define np_flipbit(data,offset)			(((data>>offset)&1)?(data ^= (1<<offset)):(data |= (1<<offset)))

// Autres
#define np_round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

/*
-----------------------------------------------------------------------------------------------
 debug
-----------------------------------------------------------------------------------------------
*/

#ifdef NP_DEBUG
#include <stdio.h>
#include <stdlib.h>
#define NP_RESULT(caller,text,code) npResult(caller,text,code)
void npResult(char* caller,char* text,int code);

extern char log_buf[];
extern char* log_ofs;
extern char* log_end;
extern FILE* log_fp;
extern NP_LOG_FUNC npLogOut;

char* npLogToFile(char* buf,char* end);

#define NP_LOG(txt,...) ( (log_ofs=strParse(log_ofs,log_end,"** %a => %d\t: ",__FUNCTION__,__LINE__))!=0 && (log_ofs=strParse(log_ofs,log_end,txt,__VA_ARGS__))!=0 && (log_ofs=strCopy(log_ofs,log_end,"\n"))!=0) ? log_ofs=npLogOut(log_buf,log_ofs) : 0
#else
#define NP_RESULT(caller,text,code) ;
#define NP_LOG(txt,...) ;
#endif

/*
-----------------------------------------------------------------------------------------------
 Base fonctions
-----------------------------------------------------------------------------------------------
*/


#include <l1/str.h>
#include <l1/int32.h>
#include <l1/memory.h>
#include <l1/stack.h>
#include <l1/chunkstack.h>
#include <l1/desc.h>
#include <l1/file.h>
#include <l1/log.h>
#include <l1/node.h>
	
#ifdef __cplusplus
}
#endif

#endif
