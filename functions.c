#include <stdbool.h>
#include <stddef.h>

bool conjunction(bool a, bool b)
{
    return a && b;
}

bool disjunction(bool a, bool b)
{
    return a || b;
}

bool implication(bool a, bool b)
{
    return !a || b;
}

bool non_implication(bool a, bool b)
{
    return a && !b;
}

bool equivalence(bool a, bool b)
{
    return a == b;
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

typedef bool (*Operation)(bool, bool);

Operation get_op(char op)
{
    switch (op)
    {
    case '&':
        return conjunction;
    case '+':
        return disjunction;
    case '>':
        return implication;
    case '<':
        return non_implication;
    case '=':
        return equivalence;
    case '^':
        return exclusive_or;
    case '~':
        return nor;
    case '|':
        return nand;
    default:
        return NULL;
    }
}
