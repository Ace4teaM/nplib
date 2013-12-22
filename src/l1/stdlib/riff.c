#include "riff.h"

/**
	@brief Reads RIFF header and advance the file pointer thereof
	@param fp File pointer
	@param header Output header structure
	@return true
*/
bool riff_fread(FILE* fp,RIFF* header){
	fread(header->id,sizeof(header->id),1,fp);
	header->size = ftoi(fp);
	return true;
}

/**
	@brief Write RIFF header and advance the file pointer thereof
	@param fp File pointer
	@param header Input header structure
	@return true
*/
bool riff_fwrite(FILE* fp,const RIFF* header){
	fwrite(header->id,sizeof(header->id),1,fp);
	itof(fp,header->size);
	return true;
}

/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST
TEST(RIFF, fread_fwrite) {
	RIFF riff = {{'R','I','F','F'},sizeof(RIFF_HEADER)};
	RIFF_HEADER head = {{'F','M','T',' '}};
	RIFF r_riff;
	RIFF_HEADER r_head;
    FILE* fp;
	if(fp = fopen("test.riff","wb")){
		riff_fwrite(fp,&riff);
		fwrite(&head,sizeof(head),1,fp);
		fclose(fp);
	}
	
	if(fp = fopen("test.riff","rb")){
		riff_fread(fp,&r_riff);
		fread(&r_head,sizeof(head),1,fp);
		fclose(fp);

		if(memcmp(&riff,&r_riff,sizeof(riff)) != 0)
			FAIL();
		if(memcmp(&head,&r_head,sizeof(riff)) != 0)
			FAIL();
	}
}

#endif