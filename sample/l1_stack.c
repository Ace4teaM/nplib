#include <stdio.h>
#include <l1/stack.h>

void show_stack_infos();

char data[200],*pstr;
NP_STACK* stack = (NP_STACK*)data;

int main()
{
	if(!npMakeStack(data,data+sizeof(data),0,100))
		return 1;

	show_stack_infos();
	
	puts("\nnpStackReserve 20+20");
	npStackReserve(stack,20);
	npStackReserve(stack,20);
	
	show_stack_infos();
	
	puts("\nnpStackPush 'hello'");
	pstr = (char*)npStackPush(stack,"hello",6);
	puts(pstr);
	
	show_stack_infos();
	
	puts("\nnpStackPop 'hello'");
	npStackPop(stack,pstr);
	
	show_stack_infos();
	
	puts("\nnpStackReset");
	npStackReset(stack);
	
	show_stack_infos();
	
	return 0;
}

void show_stack_infos()
{
	printf("Stack size: %d/%d bytes (%d used)\n",npStackFreeSize(stack),npStackSize(stack),npStackUsedSize(stack));
}
