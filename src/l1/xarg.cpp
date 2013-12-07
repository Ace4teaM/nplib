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
char* xarg_encode_field(char* out,const char* title,const char* msg) {
	//Les caracteres de controle de debut et de fin de valeur sont interdits
	for (size_t i=0;i<strlen(title);i++){
		if(title[i] != XARG_START_OF_TEXT_CODE || title[i] != XARG_END_OF_TEXT_CODE)
			*out++ = title[i];
	}
	*out++ = XARG_START_OF_TEXT_CODE;
	for (size_t i=0;i<strlen(msg);i++){
		if(msg[i] != XARG_START_OF_TEXT_CODE || msg[i] != XARG_END_OF_TEXT_CODE)
			*out++ = msg[i];
	}
	*out++ = XARG_END_OF_TEXT_CODE;
	*out = 0;
	return out;
}

/* Encode un champ dans le format XARG */
const char* xarg_decode_field(const char* in,char* title,char* msg) {
	char* cur = title;
	char c;
	while((c = *in++) != '\0'){
		switch(c){
			case XARG_START_OF_TEXT_CODE:
				*cur++ = '\0';
				cur = msg;
				break;
			case XARG_END_OF_TEXT_CODE:
				*cur++ = '\0';
				return in;
			default:
				*cur++ = c;
				break;
		}
	}
	return in;
}


/* Convertie une chaine au format XARG en tableau associatif */
int xarg_decode(void* out, int ofs, const char* text) {//v4
	char* _out=(char*)out;
	int i=0;
	int cnt=0;
	while(*text != '\0'){

		text = xarg_decode_field(text,&_out[i],&_out[i+ofs]);
		i+=ofs*2;
		cnt++;
	}
	return cnt;
//    return &_out[i+ofs];
}


/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST
TEST(XARG, xarg_encode_field) {
    char value[200];
    char expected[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,0};

    xarg_encode_field(value,"hello","world");

    ASSERT_STREQ(value, expected) << "Should be equal";
}

TEST(XARG, xarg_encode_field2) {
    char value[200];
    char* pvalue = value;
    char text[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,'f','o','o',XARG_START_OF_TEXT_CODE,'b','a','r',XARG_END_OF_TEXT_CODE,0};

    pvalue = xarg_encode_field(pvalue,"hello","world");
    pvalue = xarg_encode_field(pvalue,"foo","bar");

    ASSERT_STREQ(value, text) << "Should be equal";
}

TEST(XARG, xarg_decode_field) {
    char title[20];
    char msg[20];
    char value[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,0};

	xarg_decode_field(value,title,msg);

    ASSERT_STREQ(title, "hello") << "Should be equal";
    ASSERT_STREQ(msg, "world") << "Should be equal";
}

TEST(XARG, xarg_decode) {
    char out[20][20];
    char text[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,'f','o','o',XARG_START_OF_TEXT_CODE,'b','a','r',XARG_END_OF_TEXT_CODE,0};

	int cnt = xarg_decode(out, 20, text);
	
    ASSERT_EQ(2,cnt) << "Should be equal";
    ASSERT_STREQ(out[0], "hello") << "Should be equal";
    ASSERT_STREQ(out[1], "world") << "Should be equal";
    ASSERT_STREQ(out[2], "foo") << "Should be equal";
    ASSERT_STREQ(out[3], "bar") << "Should be equal";
}

#endif
