#include "riff.h"

/**
	@brief Reads RIFF header and advance the file pointer thereof
	@param fp File pointer
	@param header Output header structure
	@return true
*/
bool riff_read(PTR* mem,RIFF* header){
	bread(mem,header->id,sizeof(header->id));
	header->size = btoi(mem);
	return true;
}

/**
	@brief Write RIFF header and advance the file pointer thereof
	@param fp File pointer
	@param header Input header structure
	@return true
*/
bool riff_write(PTR* mem,const RIFF* header){
	bwrite(mem,header->id,sizeof(header->id));
	itob(mem,header->size);
	return true;
}

/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST
TEST(RIFF, read_write) {
	RIFF riff = {{'R','I','F','F'},sizeof(RIFF_HEADER)};
	RIFF_HEADER head = {{'F','M','T',' '}};
	RIFF r_riff;
	RIFF_HEADER r_head;

	//buffer
    char buf[200];
	PTR mem = {buf,buf+sizeof(buf),buf};

	//ecrit
	riff_write(&mem,&riff);
	bwrite(&mem,&head,sizeof(head));

	//lit
	brewind(&mem);
	riff_read(&mem,&r_riff);
	bread(&mem,&r_head,sizeof(r_head));

	if(memcmp(&riff,&r_riff,sizeof(riff)) != 0)
		FAIL() << "riff";
	if(memcmp(&head,&r_head,sizeof(riff)) != 0)
		FAIL() << "head";
}

#endif