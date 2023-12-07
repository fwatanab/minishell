#include "../inc/minishell.h"

int unset(t_node *node, t_envval *envval)
{
    size_t size;
    t_env *tmp;
    t_env *tmp_back;

    size = 1;
    while (node->args[size] != NULL)
    {
        tmp = envval->env;
        tmp_back = tmp;
        while (ft_strcmp(node->args[size], tmp->key) != 0 && tmp->next)
        {
            tmp_back = tmp;
            tmp = tmp->next;
        }
        if (tmp->next)
        {
            if (tmp == envval->env)
                envval->env = tmp->next;
            else if (tmp->next)
                tmp_back->next = tmp->next;
        }
        else
            tmp_back->next = NULL;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
        size++;
    }
    return (0);
}

t_node	*make_node(enum e_type node_type, char **args)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	node->type = node_type;
	node->name = args[0];
	node->args = args;
	return (node);
}

int	main(int ac, char **av, char **envp)
{
	t_node	*node;
	// t_env	*env;
    t_envval *envval;
    char    **array;
    int     size = 0;
	char	*unset_arg[] = {"export", "MallocNanoZone", NULL};

	node = make_node(N_COMMAND, unset_arg);
	envval = make_envval(new_envs(envp));
	unset(node, envval);
    array = make_env_strs(envval->env);
    envs_free(envval->env);
    free(envval);
    while (array[size] != NULL)
    {
        printf("%s\n", array[size]);
        size++;
    }
	free(node);
    str_array_free(array);
	// envs_str_free(env, array);
}

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }
