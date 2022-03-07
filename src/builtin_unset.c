/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:34:23 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/03 20:48:14 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_dl_list	*find_variable(t_shstate *state, char *name);

void	builtin_unset(t_shstate *state, t_cmd	*cmd)
{
	t_dl_list	*var;

	var = NULL;
	if (cmd->argv[1])
		var = find_variable(state, cmd->argv[1]);
	if (var)
		unset_var(var);
}

static t_dl_list	*find_variable(t_shstate *state, char *name)
{
	t_dl_list	*var_list;

	var_list = state->var_list;
	while (var_list)
	{
		if (var_list->content)
		{
			if (ft_strcmp(((t_variable *)(var_list->content))->key, name) == 0)
				return (var_list);
		}
		var_list = var_list->next;
	}
	return (NULL);
}
