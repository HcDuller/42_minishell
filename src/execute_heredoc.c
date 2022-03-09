/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:42:11 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/09 18:43:37 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	forked_heredoc(t_cmd *cmd, t_dl_list *cmd_lst);
static void	wait_heredoc(t_cmd	*cmd, t_shstate	*state);

void	execute_heredocs(t_shstate *state)
{
	t_dl_list	*cmd_lst;

	cmd_lst = state->cmds;
	while (cmd_lst)
	{
		if (((t_cmd *)cmd_lst->content)->type == UNEXPECTED_TOKEN)
			break ;
		if (((t_cmd *)cmd_lst->content)->type == HEREDOC)
		{
			forked_heredoc(((t_cmd *)cmd_lst->content), cmd_lst);
			wait_heredoc(((t_cmd *)cmd_lst->content), state);
		}
		cmd_lst = cmd_lst->next;
	}
}

static void	forked_heredoc(t_cmd *cmd, t_dl_list *cmd_lst)
{
	cmd->p_id = fork();
	set_child_handlers(cmd->p_id);
	if (cmd->p_id == 0)
	{
		while (cmd_lst)
		{
			if (cmd_lst->content != cmd)
				close_io(cmd);
			cmd_lst = cmd_lst->next;
		}
		heredoc(cmd);
		exit(EXIT_SUCCESS);
	}
	close(cmd->write);
}

static void	wait_heredoc(t_cmd	*cmd, t_shstate	*state)
{
	char		*exit_code;

	if (cmd->p_id != 0 && cmd->type == HEREDOC)
	{
		waitpid(cmd->p_id, &cmd->exit_status, 0);
		if (WIFEXITED(cmd->exit_status))
		{
			cmd->exit_status = WEXITSTATUS(cmd->exit_status);
		}
		else if (WIFSIGNALED(cmd->exit_status))
			cmd->exit_status |= 128;
		state->exit_code = cmd->exit_status;
		exit_code = ft_itoa(state->exit_code);
		set_var(state, "?", exit_code);
		if (exit_code)
			free(exit_code);
	}
}
