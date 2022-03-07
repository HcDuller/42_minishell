/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_cmd_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:35:46 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 20:48:41 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_file(t_cmd	*cmd);
static int	is_builtin(t_cmd	*cmd);
static int	isvar_atribution(t_cmd	*cmd);

void	define_cmd_type(t_cmd	*cmd)
{
	if (cmd)
	{
		if (cmd->l_operator == D_LESSTHAN)
			cmd->type = HEREDOC;
		else if (isvar_atribution(cmd))
			cmd->type = VAR_DECLARATION;
		else if (is_file(cmd))
			cmd->type = FILE_;
		else if (is_builtin(cmd))
			cmd->type = BUILTIN;
		else
			cmd->type = BIN;
	}
}

static int	isvar_atribution(t_cmd	*cmd)
{
	if (cmd->argv)
		return (eval_var_atribution(cmd->argv[0]));
	return (0);
}

static int	is_file(t_cmd	*cmd)
{
	if (cmd)
	{
		if (cmd->type == UNDEFINED)
		{
			if (cmd->l_operator == S_GREATERTHAN || \
				cmd->l_operator == D_GREATERTHAN)
				return (1);
			if (cmd->l_operator == S_LESSTHAN)
			{
				return (1);
			}
		}
	}
	return (0);
}

static int	is_builtin(t_cmd	*cmd)
{
	int		i;
	char	*builtins[7];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	if (cmd)
	{
		if (cmd->type == UNDEFINED && cmd->argv)
		{
			i = 0;
			while (i < 7)
			{
				if (ft_strcmp(cmd->argv[0], builtins[i]) == 0)
					return (1);
				i++;
			}
		}
	}
	return (0);
}
