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
char* _xarg_encode_field(char* up, char* down,const char* title,const char* msg) {
	size_t free_size  = (size_t)(down-up);
	size_t total_size = strlen(title) + strlen(msg) + 2 + 1;
	size_t i;
	
	//invalid size ?
	if(free_size < total_size)
		return 0;

	// copie le titre
	i=0;
	do{
		if(title[i] != XARG_START_OF_TEXT_CODE || title[i] != XARG_END_OF_TEXT_CODE)
			*up++ = title[i];
	}while(title[++i] != '\0');

	// separateur
	*up++ = XARG_START_OF_TEXT_CODE;

	// copie le message
	i=0;
	do{
		if(msg[i] != XARG_START_OF_TEXT_CODE || msg[i] != XARG_END_OF_TEXT_CODE)
			*up++ = msg[i];
	}while(msg[++i] != '\0');

	// separateur
	*up++ = XARG_END_OF_TEXT_CODE;

	//fin de chaine
	*up = 0;

	return up;
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

    ASSERT_STREQ(expected, value) << "Should be equal";
}

TEST(XARG, xarg_encode_field2) {
    char value[200];
    char* pvalue = value;
    char text[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,'f','o','o',XARG_START_OF_TEXT_CODE,'b','a','r',XARG_END_OF_TEXT_CODE,0};

    pvalue = xarg_encode_field(pvalue,"hello","world");
    pvalue = xarg_encode_field(pvalue,"foo","bar");

    ASSERT_STREQ(text, value) << "Should be equal";
}


TEST(XARG, _xarg_encode_field) {
    char value[200];
    char* pup = value;
    char* pdown = value+sizeof(value);
    char text[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,'f','o','o',XARG_START_OF_TEXT_CODE,'b','a','r',XARG_END_OF_TEXT_CODE,0};
	
	memset(value,0,sizeof(value));
    pup = _xarg_encode_field(pup,pdown,"hello","world");
    pup = _xarg_encode_field(pup,pdown,"foo","bar");

    ASSERT_STREQ(text,value) << "Should be equal";
}

TEST(XARG, xarg_decode_field) {
    char title[20];
    char msg[20];
    char value[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,0};

	xarg_decode_field(value,title,msg);

    ASSERT_STREQ("hello", title) << "Should be equal";
    ASSERT_STREQ("world", msg) << "Should be equal";
}

TEST(XARG, xarg_decode) {
    char out[20][20];
    char text[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,'f','o','o',XARG_START_OF_TEXT_CODE,'b','a','r',XARG_END_OF_TEXT_CODE,0};

	int cnt = xarg_decode(out, 20, text);
	
    ASSERT_EQ(2,cnt) << "Should be equal";
    ASSERT_STREQ("hello", out[0]) << "Should be equal";
    ASSERT_STREQ("world", out[1]) << "Should be equal";
    ASSERT_STREQ("foo", out[2]) << "Should be equal";
    ASSERT_STREQ("bar", out[3]) << "Should be equal";
}

#endif