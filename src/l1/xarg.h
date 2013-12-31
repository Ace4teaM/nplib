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
#ifndef _XARG_H
#define _XARG_H

#include "memory.h"
#include <string.h>

//#define ARDUINO 

#ifndef ARDUINO 
#define XARG_START_OF_TEXT_CODE 0x02
#define XARG_END_OF_TEXT_CODE 0x03
#else
#define XARG_START_OF_TEXT_CODE '='
#define XARG_END_OF_TEXT_CODE '\n'
#endif

extern "C" {

/**
 * @brief Encode un champ dans le format XARG
 *
 * @param mem Pointeur sur le tampon mémoire
 * @param title Titre du paramétre (Format identifier recommandé)
 * @param msg Valeur du paramétre
 * @return chaine au format XARG
 */
bool xarg_encode_field(PTR* mem,const char* title,const char* msg);

/**
 * @brief Encode un champ dans le format XARG
 *
 * @param mem Pointeur sur le tampon mémoire
 * @param string $title Titre du paramétre (Format identifier recommandé)
 * @param string $title Valeur du paramétre
 * @return chaine au format XARG
 */
bool xarg_decode_field(PTR* mem,char* title,char* msg);

/**
 * @brief Convertie une chaine au format XARG en tableau associatif
 * @param out     Tableau de tableau de type char recupérant les données 
 * @param ofs     Taille d'un mot dans out
 * @param text     Corps du texte XARG
 * @return Nombre d'items lu
*/
int xarg_decode(PTR* out, int ofs, const char* text);
}


#endif
