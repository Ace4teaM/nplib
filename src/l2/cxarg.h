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

#ifndef _NP_L2_XARG
#define _NP_L2_XARG

#include "../l1/xarg.h"
#include "../l1/str.h"
#include <map>

/**
    @brief Tableau associatif initialisable avec une chaine XARG
*/
class XARG : public std::map<std::string, std::string>{
public:
    /**
        @brief Contructeur
        @param str Chaine au format XARG
        @param trim Supprime les caractères invisible de début et fin pour chaque clés
    */
    XARG(const char* str, bool trim=true);
};

#endif
