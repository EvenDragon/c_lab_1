#include <stdbool.h>

bool implication(bool a, bool b)
{
    return !a || b;
}

bool exclusive_or(bool a, bool b)
{
    return a != b;
}

bool nor(bool a, bool b)
{
    return !(a || b);
}

bool nand(bool a, bool b)
{
    return !(a && b);
}

bool expression(bool a, bool b, bool c)
{
    return (implication(a,b) && implication(b,c));
}