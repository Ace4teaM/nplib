#ifndef _NP_L2_XARG
#define _NP_L2_XARG

#include "../l1/xarg.h"
#include <stdio.h>
#include <iostream>
#include <map>

class XARG : public std::map<std::string, std::string>{
public:
    XARG(const char* str, bool trim=true);
};

#endif
