#include <stdio.h>
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


int main(void)
{
    printf("a b | impl xor nor nand\n");
    for (int a = 0; a < 2; a++)
    {
        for (int b = 0; b < 2; b++)
        {
            printf("%d %d | %d    %d   %d   %d\n", a, b, implication(a,b), exclusive_or(a,b),
                                    nor(a,b), nand(a,b));

        }
        
    }
    
    

    return 0;
}