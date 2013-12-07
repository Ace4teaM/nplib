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
#ifdef ARDUINO
#include <arduino.h>
#endif
#include <string.h>

extern "C" {

/**
*  @brief D�finit le r�sultat en cours comme succ�s
*  @return true
*/
bool RESULT_OK();

/**
*  @brief D�finit le r�sultat en cours
*  @param context Chaine contenant le contexte de l'erreur. G�n�ralement l'une des chaines suivantes ERR_OK, ERR_FAILED, ERR_SYSTEM
*  @param code Chaine contenant le code de l'erreur. Ce code est sp�cifique � l'application
*  @return true si le code est �gale � ERR_OK, sinon false
*/
bool RESULT(const char* context, const char* code);

/**
*  @brief Retourne le code de l'erreur en cours
*  @remarks Attention get_result_code() ne retourne pas une copie de la chaine mais le pointeur global. Sa valeur est soumise � changement au prochain appel de la fonction RESULT
*  @return Chaine contenant le code
*/
const char* get_result_code();

/**
*  @brief Retourne le contexte de l'erreur en cours
*  @remarks Attention get_result() ne retourne pas une copie de la chaine mais le pointeur global. Sa valeur est soumise � changement au prochain appel de la fonction RESULT
*  @return Chaine contenant le contexte
*/
const char* get_result();
}
