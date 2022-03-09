/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:28:43 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/09 15:29:28 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	open_file(t_cmd	*cmd)
{
	int	new_fd;

	new_fd = -1;
	if (cmd->l_operator == S_LESSTHAN)
		new_fd = open(cmd->argv[0], O_RDONLY);
	if (cmd->l_operator == S_GREATERTHAN)
		new_fd = open(cmd->argv[0], O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	if (cmd->l_operator == D_GREATERTHAN)
		new_fd = open(cmd->argv[0], O_APPEND | O_CREAT | O_TRUNC, 0000644);
	if (new_fd != -1)
	{
		cmd->read = new_fd;
		cmd->write = new_fd;
	}
}

void	set_file_redirections(t_cmd	*cmd)
{
	if (cmd->type == FILE_)
	{
		open_file(cmd);
	}
}

void	set_heredoc_pipe_redir(t_cmd	*cmd)
{
	int		hrdoc[2];

	if (pipe(hrdoc) == 1)
		perror("Error");
	else
	{
		cmd->write = hrdoc[1];
		cmd->read = hrdoc[0];
	}
}

void	set_pipe_redirections(t_dl_list	*cmd_lst, int	**pipes, int	*i)
{
	t_cmd	*cmd;

	cmd = cmd_lst->content;
	if (cmd->type == BIN || cmd->type == BUILTIN || cmd->type == INVALID_BIN)
	{
		if (cmd->l_operator == PIPE)
			cmd->read = pipes[*i - 1][0];
		while (cmd_lst)
		{
			if (((t_cmd *)cmd_lst->content)->r_operator == PIPE)
			{
				cmd->write = pipes[*i][1];
				(*i) += 1;
				break ;
			}
			cmd_lst = cmd_lst->next;
		}
	}
	else if (cmd->type == HEREDOC)
	{
		set_heredoc_pipe_redir(cmd);
	}
}
