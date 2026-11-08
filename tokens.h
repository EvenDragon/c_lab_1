#ifndef TOKENS_H
#define TOKENS_H

typedef enum
{
    VAR,
    CONST,
    NOT,
    AND,
    OR,
    IMPL,
    XOR,
    EQUAL,
    NIMPL,
    NOR,
    NAND,
    L_PAREN,
    R_PAREN,
    END,
    ERROR
} TokenType;

typedef struct 
{
    TokenType type;
    char value;
}Token;

#endif