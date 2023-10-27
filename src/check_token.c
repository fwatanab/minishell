#include "../inc/minishell.h"

void	check_token(t_token_list *list)
{
	t_token_list *tmp;
	t_token_list *new;

	tmp = list;
	while (tmp->next)
	{
		if ((ft_strcmp(tmp->token, "<") == 0 && ft_strcmp(tmp->next->token, "<") == 0)
			|| (ft_strcmp(tmp->token, ">") == 0 && ft_strcmp(tmp->next->token, ">") == 0))
		{
			tmp->token = ft_strjoin(tmp->token, tmp->next->token);
			new = tmp->next->next;
			free(tmp->next);
			tmp->next = new;
		}
		tmp = tmp->next;
	}
}
