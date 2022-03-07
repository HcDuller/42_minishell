/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:02:00 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/07 17:29:13 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		execute_cmd_list(t_shstate	*state);
static	int	find_closing_quote(char *str, char quote);
int			input_is_incomplete(char *ptr);

int	main(void)
{
	t_shstate	state;

	load_state(&state);
	while (state.keep_alive)
	{
		set_shell_handlers();
		state.input = get_input();
		if (state.input)
		{
			exec_input(&state);
		}
		else
		{
			printf("\nexit");
			state.keep_alive = 0;
		}
	}
	unload_state(&state);
	return (state.exit_code);
}

void	execute_cmd_list(t_shstate	*state)
{
	t_dl_list	*cmd_list;
	int			pipe_fds[2];

	cmd_list = state->cmds;
	while (cmd_list)
	{
		if (pipe(pipe_fds) == -1)
		{
			perror("Failed to create a pipe");
		}
		cmd_list = cmd_list->next;
	}
}

int	input_is_incomplete(char *ptr)
{
	int		increment;
	char	*input;

	input = ptr;
	if (input)
	{
		while (*input)
		{
			if (*input == '"' || *input == '\'')
			{
				increment = find_closing_quote(input, (char )*input);
			}
			else
				increment = 0;
			if (increment == -1)
				return (1);
			else
				input += increment + 1;
		}
		r_trim(ptr);
		if (get_last(ptr) == '|')
			return (3);
	}
	return (0);
}

static	int	find_closing_quote(char *str, char quote)
{
	char	*next_q;

	next_q = ft_strchr(str + 1, quote);
	if (next_q == 0)
		return (-1);
	else
		return (next_q - str);
}
