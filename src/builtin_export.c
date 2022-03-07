/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:04:58 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 16:55:38 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	split_param(t_cmd	*cmd);

void	builtin_export(t_shstate	*state, t_cmd	*cmd)
{
	t_variable	*var;

	if (cmd->argv[1])
	{
		split_param(cmd);
		if (eval_varname(cmd->argv[0]))
		{
			var = get_variable(state, cmd->argv[0]);
			if (var)
			{
				if (cmd->argv[1])
					update_var(var, cmd->argv[1]);
			}
			else
			{
				set_var(state, cmd->argv[0], cmd->argv[1]);
				var = get_variable(state, cmd->argv[0]);
			}
			var->exported = 1;
		}
	}
}

static void	split_param(t_cmd	*cmd)
{
	int		i;
	char	**new_argv;

	if (cmd)
	{
		new_argv = split_in_two(cmd->argv[1]);
		i = 0;
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
			cmd->argv[i] = NULL;
			i++;
		}
		free(cmd->argv);
		cmd->argv = new_argv;
	}
}
