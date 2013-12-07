#include <np.h>
#include "l1/int32.c"
#include "l1/memory.c"
#include "l1/stack.c"
#include "l1/chunkstack.c"
#include "l1/str.c"
#include "l1/desc.c"
#include "l1/file.c"
#include "l1/log.c"
#include "l1/node.c"

#ifdef NP_DEBUG
void npResult(char* caller,char* text,int code)
{
	if(code)
	{
		NP_LOG("Serval error: %a: %a [%i]\n",caller,text,code);
		exit(code);
	}
}

char log_buf[1024];
char* log_ofs=log_buf;
char* log_end=log_buf+sizeof(log_buf);
FILE* log_fp=0;
NP_LOG_FUNC npLogOut=npLogToFile;

char* npLogToFile(char* buf,char* end)
{
	if(log_fp==0)
		log_fp=stdout;
	*end=0;

	//out
	fputs(buf,log_fp);

	return buf; //reinit buffer
}

#endif
