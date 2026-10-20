#include <stdio.h>
#include <stdbool.h>

bool implication(bool a, bool b)
{
    return !a || b;
}

int main(void)
{
    printf("a b | impl\n");
    for (int a = 0; a < 2; a++)
    {
        for (int b = 0; b < 2; b++)
        {
            printf("%d %d | %d\n", a, b, implication(a,b));

        }
        
    }
    
    

    return 0;
}