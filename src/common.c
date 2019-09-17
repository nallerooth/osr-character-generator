#include "common.h"

int roll(int ndie, int sides)
{
    int val = 0;
    while (ndie-- > 0) {
        val += (rand() % sides) + 1;
    }
    return val;
}
