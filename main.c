#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "tokens.h"
#include "functions.c"
#define MAX_FORMULA_L 100
#define MAX_VARS 20
#define PATH "test3.txt"

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

char unleash_var(char a, int *values, char vars[], int vars_count)
{
    for (int i = 0; i < vars_count; i++)
    {
        if (vars[i] == a)
            return (char)*(values+i);
    }
    return a;
}

void calculate(int *values,char vars[], int vars_count, char arr[], int arr_count,
                char *sdnf, char *scnf, int table[][vars_count + 1], int *row_count)
{
    char *tmp_arr = malloc(arr_count*sizeof(*tmp_arr));
    for (int i = 0; i < arr_count; i++)
    {
        if (arr[i] >= '0' && arr[i] <= '9')
            *(tmp_arr+i) = arr[i] - '0';
        else
            *(tmp_arr+i) = unleash_var(arr[i], values, vars, vars_count);
    }
    int tmp_l = arr_count;
    while (tmp_l>1)
    {
        for (int i = 0; i < tmp_l; i++)
        {
            int shift = 0;
            if (*(tmp_arr+i) == '!')
            {
                char a = *(tmp_arr+i-1);
                *(tmp_arr+i) = (char)(!(bool)a);
                shift = 1;
            }
            else if (*(tmp_arr+i) != '\0' && strchr("&+^=><~|", *(tmp_arr+i)) != NULL)
            {
                char a = *(tmp_arr+i-2);
                char b = *(tmp_arr+i-1);
                Operation op = get_op(*(tmp_arr+i));
                *(tmp_arr+i) = op((bool)a, (bool)b);
                shift = 2;
            }
            for (int j = i; j < tmp_l; j++)
            {
                *(tmp_arr+j-shift) = *(tmp_arr+j);
            }
            tmp_l-=shift;
            i-=shift;
        }
    }
    printf("%d | ", (int)*tmp_arr);
    for (int i = 0; i < vars_count; i++)
        table[*row_count][i] = values[i];
    table[*row_count][vars_count] = (int)*tmp_arr;
    (*row_count)++;
    if((int)*tmp_arr==1)
    {
        char *vals = malloc((5*(4+vars_count))*sizeof(*sdnf));
        int pos = 0;
        vals[pos++] = '(';

        for (int i = 0; i < vars_count; i++)
        {
            if (values[i] == 0)
                vals[pos++] = '!';

            vals[pos++] = vars[i];

            if (i < vars_count - 1)
                vals[pos++] = '&';
        }

        vals[pos++] = ')';
        vals[pos++] = '+';
        vals[pos] = '\0';
        strcat(sdnf, vals);
        free(vals);
    }
    else
    {
        char *vals = malloc((5*(4+vars_count))*sizeof(*sdnf));
        int pos = 0;
        vals[pos++] = '(';

        for (int i = 0; i < vars_count; i++)
        {
            if (values[i] == 1)
                vals[pos++] = '!';

            vals[pos++] = vars[i];

            if (i < vars_count - 1)
                vals[pos++] = '+';
        }

        vals[pos++] = ')';
        vals[pos++] = '&';
        vals[pos] = '\0';
        strcat(scnf, vals);
        free(vals);
    }
    free(tmp_arr);
}

void recursive(int *values, int pos, char vars[], int vars_count, char arr[], int arr_count,
                char *sdnf, char *scnf, int table[][vars_count + 1], int *row_count)
{
    if(pos==vars_count)
    {
        for (int i = 0; i < vars_count; i++)
        {
            printf("%d | ", *(values+i));
        }
        calculate(values, vars, vars_count, arr, arr_count,sdnf,scnf, table, row_count);
        printf("\n");
        return;
    }
    *(values+pos) = 0;
    recursive(values, pos+1, vars,vars_count, arr, arr_count,sdnf,scnf, table, row_count);
    *(values+pos) = 1;
    recursive(values, pos+1, vars,vars_count, arr, arr_count,sdnf,scnf, table, row_count);
}

void fictional_vars(int vars_count, int table[][vars_count + 1], int row_count, char vars[])
{
    bool found = false;
    printf("\nFictional vars:");
    for (int i = 0; i < vars_count; i++)
    {
        bool fictional = true;
        int step = 1 << (vars_count - i - 1);
        for (int row = 0; row < row_count; row++)
        {
            if (table[row][i] == 0 &&
                table[row][vars_count] != table[row + step][vars_count])
            {
                fictional = false;
                break;
            }
        }
        if (fictional)
        {
            printf(" %c", vars[i]);
            found = true;
        }
    }
    if (!found)
        printf(" nah");
    printf("\n");
}

void make_table(char vars[], int vars_count, char arr[], int arr_count)
{
    printf("\n");
    for (int i = 0; i < vars_count; i++)
        printf("%c | ", vars[i]);
    printf("ans\n");
    int *values = malloc(vars_count*sizeof(*values));
    int rows = 1 << vars_count;
    int (*table)[vars_count + 1] = malloc(rows * sizeof(*table));
    int row_count = 0;
    char *sdnf = malloc(pow(2, vars_count)*(5*(4+vars_count))*sizeof(*sdnf));
    char *scnf = malloc(pow(2, vars_count)*(5*(4+vars_count))*sizeof(*scnf));
    sdnf[0] = '\0';
    scnf[0] = '\0';
    recursive(values, 0, vars,vars_count, arr, arr_count,sdnf,scnf, table, &row_count);
    if (strlen(sdnf)==0)
        strcat(sdnf, "0");
    else
        sdnf[strlen(sdnf)-1] = '\0';
    if (strlen(scnf)==0)
        strcat(sdnf, "1");
    else
        scnf[strlen(scnf)-1] = '\0';
    printf("\nSDNF: %s", sdnf);
    printf("\nSCNF: %s", scnf);
    fictional_vars(vars_count, table, row_count, vars);
    free(table);
    free(values);
    free(sdnf);
    free(scnf);
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
