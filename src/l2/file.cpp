#include "file.h"

int fileWrite(const char* filename,const char* mode,char* begin,char* end)
{
	FILE* fp;

	if(mode==0)
		mode="wb";

	fp = fopen(filename,mode);
	if(fp==0)
	{
//		NP_LOG("can't open file %a in '%a' mode",filename,mode);
		return 0;
	}

	while(begin<end && fwrite(begin,1,1,fp)==1)
		begin++;

	fclose(fp);

	return 1;
}

int fileRead(const char* filename,const char* mode,char* begin,char* end)
{
	FILE* fp;

	if(mode==0)
		mode="rb";

	fp = fopen(filename,mode);
	if(fp==0)
	{
//		NP_LOG("can't open file %a in '%a' mode",filename,mode);
		return 0;
	}

	while(begin<end && fread(begin,1,1,fp)==1)
		begin++;

	fclose(fp);

	return 1;
}

int fileCat(FILE* fp,char* begin,char* end)
{
	if(fp==0)
	{
//		NP_LOG("invalid file pointer");
		return 0;
	}

	while(begin<end && fwrite(begin,1,1,fp)==1)
		begin++;

	fclose(fp);

	return 1;
}
