#include "cxarg.h"

XARG::XARG(const char* str, bool trim){
	size_t str_size = strlen(str);
	//parse les champs
	char name[200];
	char value[200];
	while(*str != '\0'){
		str = xarg_decode_field(str,name,value);
		this->insert( std::pair<std::string,std::string>(std::string(name),std::string(value)) );
	}
}

/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST
TEST(XARG, XARG) {
	char expected[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,0};
    XARG xarg(expected);
	//printf(xarg.at("hello"));
}
#endif