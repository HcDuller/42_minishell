/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:39:53 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 19:06:15 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		count_pipes(t_dl_list *cmd_lst);

int	**allocate_pipes(t_dl_list *cmd_lst)
{
	int	pipe_count;
	int	**pipes;
	int	i;

	pipe_count = count_pipes(cmd_lst);
	pipes = ft_calloc(pipe_count + 1, sizeof(int **));
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			perror("Could not create pipe");
			kill(getpid(), SIGSTOP);
		}
		i++;
	}
	return (pipes);
}

void	close_free_pipes(int	**pipes)
{
	int	i;

	i = 0;
	if (pipes)
	{
		while (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
}

static int	count_pipes(t_dl_list *cmd_lst)
{
	int		count;
	t_cmd	*cmd;

	count = 0;
	while (cmd_lst)
	{
		cmd = (t_cmd *)cmd_lst->content;
		if (cmd->r_operator == PIPE && cmd_lst->next)
			count++;
		cmd_lst = cmd_lst->next;
	}
	return (count);
}
