/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:55:35 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/06 21:17:53 by hde-camp         ###   ########.fr       */
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
		write(STDERR_FILENO, "\nminishell: warning: here-document", 34);
		write(STDERR_FILENO, "delimited by end-of-file\n", 25);
	}
}

static void	check_heredoc(t_cmd	*cmd, char *input, char *delimiter)
{
	while (ft_strcmp(input, delimiter) != 0)
	{
		if (input)
		{
			if (cmd->write != STDOUT_FILENO)
			{
				write(cmd->write, input, ft_strlen(input));
				write(cmd->write, "\n", 1);
			}
			free(input);
		}
		input = readline("> ");
		if (!input)
		{
			write(STDERR_FILENO, "\nminishell: warning: here-document", 34);
			write(STDERR_FILENO, "delimited by end-of-file\n", 25);
			break ;
		}
	}
	free(input);
}
