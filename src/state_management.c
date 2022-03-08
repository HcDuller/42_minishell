/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:06:01 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/08 13:31:54 by hde-camp         ###   ########.fr       */
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
	state->words = NULL;
	state->var_list = NULL;
	state->cmds = NULL;
	load_env_vars(state);
}

void	unload_state(t_shstate *state)
{
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
