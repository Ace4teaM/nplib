#include "riff.h"

/**
	@brief Reads RIFF header and advance the file pointer thereof
	@param fp File pointer
	@param header Output header structure
	@return true
*/
char* riff_read(char* up, char* down,RIFF* header){
	up = bread(up,down,header->id,sizeof(header->id));
	header->size = btoi(up);
	up+=sizeof(int);
	return up;
}

/**
	@brief Write RIFF header and advance the file pointer thereof
	@param fp File pointer
	@param header Input header structure
	@return true
*/
char* riff_write(char* up, char* down,const RIFF* header){
	up = bwrite(up,down,header->id,sizeof(header->id));
	itob(up,header->size);
	up+=sizeof(int);
	return up;
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
    char buf[200],*up,*down;
	down=buf+sizeof(buf);

	//ecrit
	up=buf;
	up = riff_write(up,down,&riff);
	up = bwrite(up,down,&head,sizeof(head));

	//lit
	up=buf;
	up = riff_read(up,down,&r_riff);
	up = bread(up,down,&r_head,sizeof(r_head));

	if(memcmp(&riff,&r_riff,sizeof(riff)) != 0)
		FAIL() << "riff";
	if(memcmp(&head,&r_head,sizeof(riff)) != 0)
		FAIL() << "head";
}

#endif