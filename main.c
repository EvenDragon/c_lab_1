#include <stdio.h>
#include <stdbool.h>
#include "tokens.h"

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


int main(void)
{
        const char *input = "abc";
        int index = 1;
        int position = index;

        printf("%c\n", input[position]);
        (position)++;
        printf("%c\n", input[position]);
    return 0;
}