/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:57:50 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/06 14:58:36 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		eval_cmd(t_cmd	*cmd, char	**paths);
static int		eval_first_cmd(t_dl_list	*cmd_list);

void	eval_cmds(t_shstate *state)
{
	t_dl_list	*cmd_lst;

	cmd_lst = state->cmds;
	if (eval_first_cmd(cmd_lst))
	{
		while (cmd_lst)
		{
			eval_cmd((t_cmd *)cmd_lst->content, state->paths);
			if (((t_cmd *)cmd_lst->content)->type == INVALID)
			{
				set_var(state, "?", "2");
				cmd_lst = NULL;
			}
			else
			cmd_lst = cmd_lst->next;
		}
	}
	else
		write(STDERR_FILENO, \
		"minishell: syntax error near unexpected token `|'\n", 50);
}

static void	eval_cmd(t_cmd	*cmd, char	**paths)
{
	if (cmd)
	{
		define_cmd_type(cmd);
		validate_syntax(cmd, paths);
	}
}

static int	eval_first_cmd(t_dl_list	*cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list->content;
	if (cmd->l_operator == PIPE)
		return (0);
	if (cmd->l_operator == S_LESSTHAN)
	{
		split_cmd_in_two(cmd_list);
	}
	return (1);
}
