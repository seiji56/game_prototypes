#include "include.hpp"

#ifndef _INPUT_
#define _INPUT_

struct Input
{
    bool keys[256];
    bool mouse[5];
    bool mouseX = 0;
    bool mouseY = 0;
} In;

#endif // _INPUT_
