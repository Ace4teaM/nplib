#ifndef _SYS1
#define _SYS1

#include <stdio.h>
#include <np.h>
#include <l2/handle.h>

typedef int (*SYS1_PROC)(void* self,void* args);

/* global definitions */
#define SYS1_STACK_SIZE  4096
#define SYS1_HSIZE 64
#define SYS1_HMAX  48/2
#define SYS1_FUNC_NAME_MAXCHAR  (SYS1_HSIZE-sizeof(SYS1_PROC))

/* fonctions */
int init_sys1();

typedef struct
{
	char name[SYS1_FUNC_NAME_MAXCHAR];
	SYS1_PROC proc;
}SYS1_FUNC;

#endif
