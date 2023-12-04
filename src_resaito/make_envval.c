#include "../inc/minishell.h"

t_envval    *make_envval(t_env *env)
{
    t_envval *envval;

    envval = malloc(sizeof(t_envval) * 1);
    if (envval == NULL)
        exit(1);
    envval->env = env;
    envval->status = 0;
    return (envval);
}
