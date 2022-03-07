/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:59:25 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/05 21:02:52 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	char	*merge_inputs(char *first_read, char	*temp_read, int status);

char	*get_input(void)
{
	char	*ptr;
	char	*temp;
	int		input_status;

	ptr = NULL;
	ptr = readline("Promtp>");
	input_status = input_is_incomplete(ptr);
	while (input_status)
	{
		rl_on_new_line();
		temp = readline("> ");
		if (temp)
		{
			if (ft_strlen(temp))
			{
				ptr = merge_inputs(ptr, temp, input_status);
			}
		}
		input_status = input_is_incomplete(ptr);
	}
	return (ptr);
}

void	exec_input(t_shstate *state)
{
	if (ft_strlen(state->input))
	{
		add_history(state->input);
		input_parser(state);
		state->cmds = ft_dl_getfirst(state->cmds);
		execute_cmds(state);
		free_word_list(state);
		free_cmds(state);
	}
	free(state->input);
	state->input = NULL;
}

char	get_last(char	*str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
		i--;
		if (i > -1)
			return (str[i]);
	}
	return (0);
}

void	r_trim(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > -1 && ft_isspace(str[i]))
	{
		str[i] = 0;
		i--;
	}
}

static	char	*merge_inputs(char *first_read, char	*temp_read, int status)
{
	char	*concat;

	if (status == 3)
	{
		r_trim(temp_read);
		concat = ft_strjoin(first_read, temp_read);
	}
	else
	{
		concat = ft_strjoin(first_read, "\n");
		free(first_read);
		first_read = ft_strjoin(concat, temp_read);
		free(concat);
		concat = ft_strdup(first_read);
	}
	free(first_read);
	free(temp_read);
	first_read = concat;
	return (concat);
}
