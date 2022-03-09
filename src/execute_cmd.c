/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:31:40 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/09 18:34:55 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	execute_bin_cmd(t_cmd *cmd, t_dl_list *cmd_lst, t_shstate *state);
static void	exec_builtin(t_shstate *state, t_cmd *cmd);
static void	forked_env(t_cmd *cmd, t_dl_list *cmd_lst, t_shstate *state);

void	execute_cmd(t_shstate *state, t_dl_list	*cmd_lst)
{
	char	*temp;
	t_cmd	*cmd;

	cmd = cmd_lst->content;
	if (cmd->type == BIN)
	{
		execute_bin_cmd((t_cmd *)cmd_lst->content, \
		ft_dl_getfirst(cmd_lst), state);
	}
	else if (cmd->type == BUILTIN)
	{
		exec_builtin(state, (t_cmd *)cmd_lst->content);
	}
	else if (cmd->type == VAR_DECLARATION)
	{
		set_var(state, cmd->argv[0],
			cmd->argv[1]);
	}
	else if (cmd->type == INVALID_BIN)
	{
		temp = ft_itoa(cmd->exit_status);
		set_var(state, "?", temp);
		free(temp);
		write(STDERR_FILENO, cmd->err_msg, ft_strlen(cmd->err_msg));
	}
}

static void	exec_builtin(t_shstate *state, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		builtin_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		builtin_exit(state, cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd->argv[0], "env"))
	{
		forked_env(cmd, state->cmds, state);
	}
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		builtin_unset(state, cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		builtin_export(state, cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		builtin_cd(state, cmd);
}

void	close_io(t_cmd	*cmd)
{
	if (cmd->write != 1)
		close(cmd->write);
	if (cmd->read != 0)
		close(cmd->read);
}

static void	forked_env(t_cmd *cmd, t_dl_list *cmd_lst, t_shstate *state)
{
	cmd->p_id = fork();
	set_child_handlers(cmd->p_id);
	if (cmd->p_id == 0)
	{
		if (dup2(cmd->read, STDIN_FILENO) == -1)
			perror("error when duping read");
		if (dup2(cmd->write, STDOUT_FILENO) == -1)
			perror("error when duping write");
		while (cmd_lst)
		{
			if (cmd->type != FILE_)
			{
				close_io(cmd);
			}
			cmd_lst = cmd_lst->next;
		}
		builtin_env(state);
		unload_state(state);
		exit(EXIT_SUCCESS);
	}
	close_io(cmd);
}

static void	execute_bin_cmd(t_cmd *cmd, t_dl_list *cmd_lst, t_shstate *state)
{
	cmd->p_id = fork();
	set_child_handlers(cmd->p_id);
	if (cmd->p_id == 0)
	{
		if (dup2(cmd->read, STDIN_FILENO) == -1)
			perror("error when duping read");
		if (dup2(cmd->write, STDOUT_FILENO) == -1)
			perror("error when duping write");
		while (cmd_lst)
		{
			if (cmd->type != FILE_)
			{
				close_io(cmd);
			}
			cmd_lst = cmd_lst->next;
		}
		execve(cmd->argv[0], cmd->argv, get_state_env(state));
		perror("Binary was not executed");
	}
	close_io(cmd);
}
