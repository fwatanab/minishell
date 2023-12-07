#include "../inc/minishell.h"

static size_t  len_2_equal(char *str);

int export(t_node *node, t_envval *envval)
{
    size_t  size;
    t_env   *tmp;
    size_t  equal_len;

    size = 1;
    while (node->args[size] != NULL)
    {
        equal_len = len_2_equal(node->args[size]);
        if (equal_len == 0)
            return (1);
        tmp = envval->env;
        while (tmp->next && ft_strncmp(tmp->key, node->args[size], equal_len) != 0)
            tmp = tmp->next;
        if (ft_strncmp(tmp->key, node->args[size], equal_len) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(node->args[size] + (equal_len + 1));
        }
        else
            envadd_back(&(envval->env), new_env(node->args[size]));
        size++;
    }
    return (0);
}

static size_t  len_2_equal(char *str)
{
    size_t  len;

    len = 0;
    if (str == NULL)
        return (0);
    while (str[len] != '\0' && str[len] != '=')
        len++;
    if (str[len] != '=')
        return (0);
    return (len);
}

// t_node	*make_node(enum e_type node_type, char **args)
// {
// 	t_node	*node;

// 	node = calloc(sizeof(t_node), 1);
// 	node->type = node_type;
// 	node->name = args[0];
// 	node->args = args;
// 	return (node);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_node	*node;
// 	t_env	*env;
//     char    **array;
//     int     size = 0;
// 	char	*export_arg[] = {"export", "PATH", NULL};

// 	node = make_node(N_COMMAND, export_arg);
// 	env = new_envs(envp);
// 	export(node, env);
//     array = make_env_strs(env);
//     envs_free(env);
//     while (array[size] != NULL)
//     {
//         printf("%s\n", array[size]);
//         size++;
//     }
// 	free(node);
//     str_array_free(array);
// 	// envs_str_free(env, array);
// }

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }
