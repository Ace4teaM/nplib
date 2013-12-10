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

#include <include\l1\result.h>

/*
  codes
*/
const char* ERR_OK = "ERR_OK";
const char* ERR_FAILED = "ERR_FAILED";
const char* ERR_SYSTEM = "ERR_SYSTEM";
const char* NULL_STR = "";
const char* SUCCESS = "SUCCESS";

/*
  globals
*/
const char* g_result_context;
const char* g_result_code;

/* Définit le résultat en cours comme succès */
bool RESULT_OK(){
	g_result_context=ERR_OK;
	g_result_code=SUCCESS;
	return true;
}

/* Définit le résultat en cours */
bool RESULT(const char* context, const char* code){
	g_result_context=context;
	g_result_code=code;
	if(strcmp(context,ERR_OK) == 0)
		return true;
#ifdef ARDUINO
	Serial.print("context: ");
	Serial.print(context);
	Serial.print(", ");
	Serial.println(code);
#endif
	return false;
}

/* Retourne le code de l'erreur en cours */
const char* get_result_code(){
	return g_result_code;
}

/* Retourne le contexte de l'erreur en cours */
const char* get_result(){
	return g_result_context;
}


/*
  tests réalisés avec la librairie GoogleTest
*/
#ifdef GTEST
TEST(RESULT, result) {
    RESULT_OK();
    ASSERT_STREQ(get_result(), ERR_OK) << "Should be equal";
    ASSERT_STREQ(get_result_code(), SUCCESS) << "Should be equal";
}
#endif
