/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:22:37 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/09 19:10:16 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	validate_bin_sintax(t_cmd	*cmd, t_shstate	*state);
static void	validate_var_sintax(t_cmd	*cmd);
static void	validate_heredoc(t_cmd	*cmd);
static void	print_heredoc_error(t_cmd	*cmd);

void	validate_syntax(t_cmd	*cmd, t_shstate	*state)
{
	if (cmd)
	{
		if (cmd->type == BIN)
		{
			validate_bin_sintax(cmd, state);
		}
		if (cmd->type == VAR_DECLARATION)
		{
			validate_var_sintax(cmd);
		}
		if (cmd->type == HEREDOC)
		{
			validate_heredoc(cmd);
		}
		if (cmd->type == FILE_)
			validate_file_sintax(cmd);
	}
}

static void	validate_var_sintax(t_cmd	*cmd)
{
	int		i;
	char	**new_argv;

	if (cmd)
	{
		new_argv = split_in_two(cmd->argv[0]);
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

static void	validate_bin_sintax(t_cmd	*cmd, t_shstate	*state)
{
	int		file_exists;
	char	**paths;

	paths = load_paths(state);
	if (cmd->argv)
	{
		file_exists = 0;
		if (ft_strchr(cmd->argv[0], '/'))
		{
			file_exists = check_file(cmd->argv[0], 1);
		}
		else if (paths)
			file_exists = check_relative_file(cmd, paths);
		if (!file_exists)
		{
			cmd->err_msg = ft_strjoin(cmd->argv[0], ": command not found\n");
			cmd->type = INVALID_BIN;
			cmd->exit_status = 127;
		}
	}
	free_str_vector(paths);
}

static void	print_heredoc_error(t_cmd	*cmd)
{
	char	*base_str;
	char	*complement;

	base_str = "minishell: syntax error near unexpected token `";
	complement = NULL;
	if (cmd->r_operator == D_LESSTHAN)
		complement = "`<<";
	else if (cmd->r_operator == D_GREATERTHAN)
		complement = "`>>";
	else if (cmd->r_operator == S_LESSTHAN)
		complement = "`<";
	else if (cmd->r_operator == S_GREATERTHAN)
		complement = "`>";
	cmd->err_msg = ft_strjoin(base_str, complement);
}

static void	validate_heredoc(t_cmd	*cmd)
{
	if (cmd->argv == NULL)
	{
		cmd->type = UNEXPECTED_TOKEN;
		if (cmd->r_operator == 0)
		{
			cmd->err_msg = ft_strdup("minishell: syntax error near \
unexpected token `newline'\n");
		}
		else if (cmd->r_operator)
			print_heredoc_error(cmd);
	}
}
