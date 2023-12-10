#include "../inc/minishell.h"

int    get_exit_code(int n)
{
    if (n % 256 == 0)
        return (n / 256);
    else
        return (n % 256 + 128);
}