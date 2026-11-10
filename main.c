#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"
#include "functions.c"
#define MAX_FORMULA_L 100
#define MAX_VARS 20
#define PATH "test2.txt"

int define_priority(char op)
{
    switch (op)
    {
    case '!':
        return 1;
        break;
    case '&':
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
        return -1;
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
        else if ((('a'<=formula[i]) && (formula[i]<='z')) ||
                 (('A'<=formula[i]) && (formula[i]<='Z')))
        {
            char var = (char)tolower((unsigned char)formula[i]);
            queue[queue_pos] = var;
            queue_pos++;
            bool flag = true;
            for (int i = 0; i < vars_pos; i++)      //check for duplicates
            {
                if(vars[i]==var)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                vars[vars_pos] = var;
                vars_pos++;
            }
            
        }
        else if (strchr("!&+^=><~|", formula[i]) != NULL)
        {
            while (stack_pos > 0 && formula[i] != '!' &&
                   define_priority(stack[stack_pos - 1]) <= define_priority(formula[i]))
            {
                queue[queue_pos] = stack[stack_pos-1];
                queue_pos++;
                stack_pos--;
            }
            stack[stack_pos] = formula[i];
            stack_pos++;
        }
        else if (formula[i] == '(')
        {
            stack[stack_pos] = formula[i];
            stack_pos++;
        }
        else if (formula[i] == ')')
        {
            while (stack[stack_pos - 1] != '(')
            {
                queue[queue_pos] = stack[stack_pos-1];
                stack_pos--;
                queue_pos++;
            }
            stack_pos--;
        }
        else
            break;
    }
    while (stack_pos>0)
    {
        queue[queue_pos] = stack[stack_pos-1];
        queue_pos++;
        stack_pos--;
    }
    queue[queue_pos] = '\0';
    for (int i = 0; i < queue_pos; i++)
    {
        printf("|%c", queue[i]);
    }
    printf("\n");
    for (int i = 0; i < vars_pos; i++)
    {
        printf("|%c", vars[i]);
    }
    
    printf("\n");
    make_table(vars, vars_pos, queue, queue_pos);
}

char unleash_var(char a, int *values, char vars[], int vars_count)
{
    for (int i = 0; i < vars_count; i++)
    {
        if (vars[i] == a)
            return (char)*(values+i);
    }
    return a;
}

void calculate(int *values,char vars[], int vars_count, char arr[], int arr_count)
{
    char tmp;
    char *tmp_arr = malloc(arr_count*sizeof(*tmp_arr));
    for (int i = 0; i < arr_count; i++)
        *(tmp_arr+i) = arr[i];
    int tmp_l = arr_count;
    while (tmp_l>1)
    {
        for (int i = 0; i < tmp_l; i++)
        {
            if (*(tmp_arr+i) == '!')
            {
                /* code */
            }
            else if (strchr("0123456789", (*(tmp_arr+i))) != NULL)
            {
                /* code */
            }
        }
        
    }
    
    
}

void recursive(int *values, int pos, char vars[], int vars_count, char arr[], int arr_count)
{
    if(pos==vars_count)
    {
        for (int i = 0; i < vars_count; i++)
        {
            printf("%d ", *(values+i));
        }
        calculate(values, vars, vars_count, arr, arr_count);        
        printf("\n");
        return;
    }
    *(values+pos) = 0;
    recursive(values, pos+1, vars,vars_count, arr, arr_count);
    *(values+pos) = 1;
    recursive(values, pos+1, vars,vars_count, arr, arr_count);
}

void make_table(char vars[], int vars_count, char arr[], int arr_count)
{
    for (int i = 0; i < vars_count; i++)
        printf("%c ", vars[i]);
    printf("\n");
    int *values = malloc(vars_count*sizeof(*values));
    recursive(values, 0, vars,vars_count, arr, arr_count);
    free(values);
}

int main(void)
{
    char *path;
    path = PATH; //scanf("%s", path);
    FILE *file = fopen(path, "r");
    char formula[MAX_FORMULA_L];
    fscanf(file, "%s", formula);
    fclose(file);
    printf("%s\n", formula);
    shunting_yard_alg(formula);
    return 0;
}
