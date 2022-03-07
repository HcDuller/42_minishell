/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:06:01 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/06 19:22:38 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	load_env_vars(t_shstate *state);
static	void	str_to_var(t_shstate *state, char *str);

void	load_state(t_shstate *state)
{
	state->input = NULL;
	state->keep_alive = 1;
	state->exit_code = 0;
	state->paths = NULL;
	state->words = NULL;
	state->var_list = NULL;
	state->cmds = NULL;
	load_paths(state);
	load_env_vars(state);
}

void	unload_paths(t_shstate *state)
{
	char	**ptr;
	int		p_index;

	ptr = state->paths;
	p_index = 0;
	while (ptr[p_index])
	{
		free(ptr[p_index]);
		ptr[p_index] = NULL;
		p_index++;
	}
	free(state->paths);
	state->paths = NULL;
}

void	unload_state(t_shstate *state)
{
	unload_paths(state);
	if (state->input)
		free(state->input);
	unset_all_var(state);
}

static	void	load_env_vars(t_shstate *state)
{
	char	**def_env;
	int		i;

	def_env = __environ;
	i = 0;
	while (def_env[i])
	{
		str_to_var(state, def_env[i]);
		i++;
	}
	set_var(state, "0", "minishell");
	set_var(state, "?", "0");
}

static	void	str_to_var(t_shstate *state, char *str)
{
	t_variable	*var;
	char		*equal_char;
	char		*key;
	char		*value;

	equal_char = ft_strchr(str, '=');
	if (equal_char)
	{
		key = str;
		value = (equal_char + 1);
		*equal_char = 0;
		set_var(state, key, value);
	}
	var = NULL;
	var = get_variable(state, key);
	if (var)
		var->exported = 1;
}
