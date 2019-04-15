#include "lib.h"
#include "maths.h"

/* Common maths functions */

int abs(int n)
{
        if(n > 0)
                return n;
        else
                return -n;
}

int pow(int x, unsigned int y)
{
        int tmp;
        if(y == 0)
                return 1;
        tmp = pow(x, y/2);
        if(y % 2 == 0)
                return tmp * tmp;
        return x * tmp * tmp;
}
