/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:55:35 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/09 20:17:23 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_heredoc(t_cmd	*cmd, char *input, char *delimiter);

void	heredoc(t_cmd	*cmd)
{
	char	*input;
	char	*delimiter;

	input = readline("> ");
	delimiter = cmd->argv[0];
	if (input)
		check_heredoc(cmd, input, delimiter);
	else
	{
		ft_putstr_fd(RED, STDERR_FILENO);
		ft_putstr_fd("minishell warning: here-document \
delimited by end-of-file", STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

static void	check_heredoc(t_cmd	*cmd, char *input, char *delimiter)
{
	while (ft_strcmp(input, delimiter) != 0)
	{
		if (input)
		{
			write(cmd->write, input, ft_strlen(input));
			write(cmd->write, "\n", 1);
			free(input);
		}
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd(RED, STDERR_FILENO);
			ft_putstr_fd("minishell warning: here-document \
delimited by end-of-file", STDERR_FILENO);
			ft_putstr_fd(RESET, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			break ;
		}
	}
	free(input);
}
