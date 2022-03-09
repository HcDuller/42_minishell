/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:25:10 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/09 20:35:22 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_pipings(t_dl_list *cmd_lst, int **pipes);
static void	set_ins_outs(t_dl_list *cmd_lst);
static void	wait_cmds_to_end(t_shstate	*state);
static void	exec_cmd(t_shstate *state);

void	execute_cmds(t_shstate *state)
{
	int			**pipes;

	pipes = allocate_pipes(state->cmds);
	set_pipings(state->cmds, pipes);
	set_ins_outs(state->cmds);
	execute_heredocs(state);
	exec_cmd(state);
	close_free_pipes(pipes);
	wait_cmds_to_end(state);
}

static void	exec_cmd(t_shstate *state)
{
	t_dl_list	*cmd_lst;

	cmd_lst = state->cmds;
	if (cmd_list_should_run(cmd_lst))
	{
		while (cmd_lst)
		{
			if (((t_cmd *)cmd_lst->content)->type == INVALID_BIN)
				close_io(cmd_lst->content);
			cmd_lst = cmd_lst->next;
		}
		cmd_lst = state->cmds;
		while (cmd_lst)
		{
			execute_cmd(state, cmd_lst);
			cmd_lst = cmd_lst->next;
		}
	}
	else
	{
		print_error();
		set_var(state, "?", "2");
	}
}

static void	set_pipings(t_dl_list *cmd_lst, int **pipes)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	while (cmd_lst)
	{
		cmd = (t_cmd *)cmd_lst->content;
		set_pipe_redirections(cmd_lst, pipes, &i);
		set_file_redirections(cmd);
		cmd_lst = cmd_lst->next;
	}
}

static void	set_ins_outs(t_dl_list *cmd_lst)
{
	t_cmd	*cmd;

	while (cmd_lst)
	{
		cmd = (t_cmd *)cmd_lst->content;
		if (cmd->type == BIN || cmd->type == BUILTIN)
		{
			set_cmd_output(cmd_lst);
			set_cmd_input(cmd_lst);
		}	
		cmd_lst = cmd_lst->next;
	}
}

static void	wait_cmds_to_end(t_shstate	*state)
{
	t_dl_list	*cmd_lst;
	t_cmd		*cmd;
	char		*exit_code;

	cmd_lst = ft_dl_getfirst(state->cmds);
	while (cmd_lst)
	{
		cmd = (t_cmd *)cmd_lst->content;
		if (cmd->p_id != 0 && cmd->type != HEREDOC)
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
		cmd_lst = cmd_lst->next;
	}
}
