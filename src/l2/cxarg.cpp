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

#include "cxarg.h"

XARG::XARG(const char* str, bool trim){
	size_t str_size = strlen(str);
	//parse les champs
	char name[200];
	char value[200];
	while(*str != '\0'){
		str = xarg_decode_field(str,name,value);
		if(trim){
            char* begin=name;
            char* end=name+strlen(name);
            str_trim(&begin,&end);
            *end=0;
		}
		this->insert( std::pair<std::string,std::string>(std::string(name),std::string(value)) );
	}
}

/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST
TEST(XARG, XARG) {
    char text[]={'h','e','l','l','o',XARG_START_OF_TEXT_CODE,'w','o','r','l','d',XARG_END_OF_TEXT_CODE,'f','o','o',XARG_START_OF_TEXT_CODE,'b','a','r',XARG_END_OF_TEXT_CODE,0};
    XARG xarg(text);
    ASSERT_STREQ("world", xarg["hello"].c_str()) << "Should be equal";
    ASSERT_STREQ("bar", xarg["foo"].c_str()) << "Should be equal";
}
#endif
