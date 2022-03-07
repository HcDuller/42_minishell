/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:22:37 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 20:57:29 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	validate_bin_sintax(t_cmd	*cmd, char	**paths);
static void	validate_var_sintax(t_cmd	*cmd);
static void	validate_heredoc(t_cmd	*cmd);
static void	print_heredoc_error(t_cmd	*cmd);

void	validate_syntax(t_cmd	*cmd, char	**paths)
{
	if (cmd)
	{
		if (cmd->type == BIN)
		{
			validate_bin_sintax(cmd, paths);
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

static void	validate_bin_sintax(t_cmd	*cmd, char	**paths)
{
	int	file_exists;

	if (cmd->argv)
	{
		if ((char)*cmd->argv[0] == '/')
		{
			file_exists = check_file(cmd->argv[0], 1);
		}
		else
		{
			file_exists = check_relative_file(cmd, paths);
		}
		if (!file_exists)
		{
			write(STDERR_FILENO, cmd->argv[0], ft_strlen(cmd->argv[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			cmd->type = INVALID_BIN;
		}
	}
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
	write(STDERR_FILENO, base_str, 47);
	write(STDERR_FILENO, complement, ft_strlen(complement));
	write(STDERR_FILENO, "\n", 1);
}

static void	validate_heredoc(t_cmd	*cmd)
{
	if (cmd->argv == NULL)
	{
		cmd->type = INVALID;
		if (cmd->r_operator == 0)
		{
			write(STDERR_FILENO, "minishell: syntax error", 23);
			write(STDERR_FILENO, "near unexpected token `newline'\n", 32);
		}
		else if (cmd->r_operator)
			print_heredoc_error(cmd);
	}
}