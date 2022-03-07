/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:50:18 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/06 20:16:24 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_variable	*get_state_var(t_shstate *state, const char *name);

const char	*get_var_value(t_shstate *state, char *name)
{
	char		*value;
	t_variable	*var;

	value = NULL;
	if (name)
	{
		var = get_state_var(state, name);
		if (var)
			return (var->value);
	}
	return (value);
}

t_variable	*get_variable(t_shstate *state, const char *name)
{
	t_dl_list	*var;
	char		*cur_key;

	var = ft_dl_getfirst(state->var_list);
	while (var)
	{
		cur_key = ((t_variable *)var->content)->key;
		if (ft_strcmp((const char *)cur_key, name) == 0)
			return (var->content);
		var = var->next;
	}
	return (NULL);
}

static t_variable	*get_state_var(t_shstate *state, const char *name)
{
	t_dl_list	*var;
	char		*cur_key;

	var = ft_dl_getfirst(state->var_list);
	while (var)
	{
		cur_key = ((t_variable *)var->content)->key;
		if (ft_strcmp((const char *)cur_key, name) == 0)
			return ((t_variable *)var->content);
		var = var->next;
	}
	return (NULL);
}
