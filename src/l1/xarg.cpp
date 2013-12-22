/*
    ---------------------------------------------------------------------------------------------------------------------------------------
    (C)2013 Thomas AUGUEY <contact@aceteam.org>
    ---------------------------------------------------------------------------------------------------------------------------------------
    This file is part of WebFrameWork.

    WebFrameWork is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    WebFrameWork is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with WebFrameWork.  If not, see <http://www.gnu.org/licenses/>.
    ---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "xarg.h"

/* Encode un champ dans le format XARG */
bool xarg_encode_field(PTR* mem,const char* title,const char* msg) {
	size_t free_size  = (size_t)(mem->down-mem->ptr);
	size_t total_size = strlen(title) + strlen(msg) + 2 + 1;
	size_t i;
	
	//invalid size ?
	if(free_size < total_size)
		return 0;

	// copie le titre
	i=0;
	do{
		if(title[i] != XARG_START_OF_TEXT_CODE || title[i] != XARG_END_OF_TEXT_CODE)
			*mem->ptr++ = title[i];
	}while(title[++i] != '\0');

	// separateur
	*mem->ptr++ = XARG_START_OF_TEXT_CODE;

	// copie le message
	i=0;
	do{
		if(msg[i] != XARG_START_OF_TEXT_CODE || msg[i] != XARG_END_OF_TEXT_CODE)
			*mem->ptr++ = msg[i];
	}while(msg[++i] != '\0');

	// separateur
	*mem->ptr++ = XARG_END_OF_TEXT_CODE;

	//fin de chaine
	*mem->ptr = 0;

	return true;
}

/* Encode un champ dans le format XARG */
bool xarg_decode_field(PTR* in,char* title,char* msg) {
	char* cur = title;
	char c;
	while((c = *in->ptr++) != '\0'){
		switch(c){
			case XARG_START_OF_TEXT_CODE:
				*cur++ = '\0';
				cur = msg;
				break;
			case XARG_END_OF_TEXT_CODE:
				*cur++ = '\0';
				return true;
			default:
				*cur++ = c;
				break;
		}
	}
	return false;
}


/* Convertie une chaine au format XARG en tableau associatif
int xarg_decode(PTR* out, int ofs, const char* text) {//v4
	int i=0;
	int cnt=0;
	while(*text != '\0'){
		text = xarg_decode_field(text,&out->ptr[i],&out->ptr[i+ofs]);
		i+=ofs*2;
		cnt++;
	}
	return cnt;
//    return &_out[i+ofs];
} */



/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST
TEST(XARG, xarg_encode_field) {
    char value[200];
    char expected[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,0};
	PTR ptr={value,value+sizeof(value),value};

    xarg_encode_field(&ptr,"hello","world");

	ASSERT_STREQ(expected, ptr.up) << "simple encoding";
}

TEST(XARG, xarg_encode_field2) {
    char value[200];
    char text[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,'f','o','o',XARG_START_OF_TEXT_CODE,'b','a','r',XARG_END_OF_TEXT_CODE,0};
	PTR ptr={value,value+sizeof(value),value};

    xarg_encode_field(&ptr,"hello","world");
    xarg_encode_field(&ptr,"foo","bar");

    ASSERT_STREQ(text, ptr.up) << "multiple encoding";
}

TEST(XARG, xarg_decode_field) {
    char title[20];
    char msg[20];
    char value[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,0};
	PTR ptr={value,value+sizeof(value),value};

	xarg_decode_field(&ptr,title,msg);

    ASSERT_STREQ("hello", title) << "Should be equal";
    ASSERT_STREQ("world", msg) << "Should be equal";
}
/*
TEST(XARG, xarg_decode) {
    char out[20][20];
    char text[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,'f','o','o',XARG_START_OF_TEXT_CODE,'b','a','r',XARG_END_OF_TEXT_CODE,0};

	int cnt = xarg_decode(out, 20, text);
	
    ASSERT_EQ(2,cnt) << "Should be equal";
    ASSERT_STREQ("hello", out[0]) << "Should be equal";
    ASSERT_STREQ("world", out[1]) << "Should be equal";
    ASSERT_STREQ("foo", out[2]) << "Should be equal";
    ASSERT_STREQ("bar", out[3]) << "Should be equal";
}*/

#endif