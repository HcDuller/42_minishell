/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:28:26 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/11 15:07:48 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_exit_code(char	*exit_code)
{
	if (exit_code)
	{
		while (*exit_code)
		{
			if (!ft_isdigit((int) *exit_code))
				return (0);
			exit_code++;
		}
		return (1);
	}
	return (0);
}

void	builtin_exit(t_shstate *state, t_cmd	*cmd)
{
	state->exit_code = 0;
	state->keep_alive = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (is_valid_exit_code(cmd->argv[1]))
	{
		state->exit_code = ft_atoi(cmd->argv[1]);
	}
	else if (cmd->argv[1])
	{
		ft_putstr_fd(RED, STDERR_FILENO);
		ft_putstr_fd("minishell: exit: numeric \
argument required", STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		state->exit_code = 2;
	}
}

char	*alloc_echo_str(char **argv)
{
	int		size;
	int		tmp_size;
	int		i;
	char	*ptr;

	size = 0;
	i = 0;
	while (argv[i])
	{
		tmp_size = ft_strlen(argv[i]);
		size += tmp_size;
		if (tmp_size > 0 && argv[i + 1])
			size++;
		i++;
	}
	ptr = ft_calloc(size + 1, sizeof(char));
	return (ptr);
}

void	builtin_echo(t_cmd	*cmd)
{
	int		i;
	int		final_size;
	int		local_size;
	char	*final_str;

	final_str = alloc_echo_str((char **)((cmd->argv) + 1));
	final_size = 0;
	i = 1;
	while ((cmd->argv)[i])
	{
		local_size = ft_strlen((cmd->argv)[i]);
		ft_memmove((void *)(final_str + final_size), \
					(void *)(cmd->argv)[i], local_size);
		final_size += local_size;
		if ((cmd->argv)[i + 1])
		{
			*((char *)(final_str + final_size)) = ' ';
			final_size++;
		}
		i++;
	}
	write(cmd->write, final_str, final_size);
	write(cmd->write, "\n", 1);
	close_io(cmd);
	free(final_str);
}
