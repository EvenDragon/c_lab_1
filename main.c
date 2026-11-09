#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "functions.c"
#define MAX_FORMULA_L 100
#define MAX_VARS 20

int define_priority(char op)
{
    switch (op)
    {
    case '!':
        return 1;
        break;
    case '%':
    case '|':
        return 2;
        break;
    case '^':
        return 3;
        break;
    case '+':
    case '~':
        return 4;
        break;
    case '>':
    case '<':
        return 5;
        break;
    case '=':
        return 6;
        break;
    case '(':
        return 10000000;
        break;
    default:
        printf("Error. Operator undefined");
        break;
    }
}

void shunting_yard_alg(char formula[])
{
    char stack[MAX_FORMULA_L];
    int stack_pos = 0;
    char vars[MAX_VARS];
    int vars_pos = 0;
    char queue[MAX_FORMULA_L];
    int queue_pos = 0;
    for (int i = 0; i < MAX_FORMULA_L; i++)
    {
        if (formula[i] == '\0')
            break;
        else if (strchr("0123456789", formula[i]) != NULL)
        {
            queue[queue_pos] = formula[i];
            queue_pos+=1;
        }
        else if (('a'<=formula[i]<='z') || ('A'<=formula[i]<='Z'))
        {
            vars[vars_pos] = (char)tolower((unsigned char)formula[i]);
            queue[queue_pos] = (char)tolower((unsigned char)formula[i]);
            vars_pos++;
            queue_pos++;
        }
        else if (strchr("!&+^=><~|", formula[i]) != NULL)
        {
            while (stack_pos>=0 && define_priority(stack[stack_pos]<=define_priority(formula[i])))
            {
                queue[queue_pos] = stack[stack_pos];
                queue_pos++;
                stack_pos--;
            }
            stack[stack_pos] = formula[i];
            stack_pos++;
        }
        else if (formula[i] == '(')
        {
            stack[stack_pos] = formula[i];
        }
        else if (formula[i] == ')')
        {
            while (stack[stack_pos] != '(')
            {
                queue[queue_pos] = stack[stack_pos];
                stack_pos--;
                queue_pos++;
            }
            stack_pos--;
        }
        else
            break;
    }
    for (int i = 0; i < MAX_FORMULA_L; i++)
    {
        printf("|%c", queue[i]);
    }
    
}

int main(void)
{
    char *path;
    path = "test.txt"; //scanf("%s", path);
    FILE *file = fopen(path, "r");
    char formula[MAX_FORMULA_L];
    fscanf(file, "%s", formula);
    fclose(file);
    printf("%s\n", formula);
    shunting_yard_alg(formula);
    return 0;
}
