#include "utils.h"

float max3(float x, float y, float z)
{
    if(x > y && x > z)
        return x;
    else if(y > x && y > z)
        return y;
    else
        return z;
}
