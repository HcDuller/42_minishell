/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:54:18 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/02 18:43:55 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_var_to_state(t_shstate *state, t_variable *var);

void	set_var(t_shstate *state, const char *name, const char *value)
{
	t_variable	*var;

	var = get_variable(state, name);
	if (var)
	{
		update_var(var, value);
	}
	else
	{
		var = create_var(name, value);
		add_var_to_state(state, var);
	}
}

static void	add_var_to_state(t_shstate *state, t_variable *var)
{
	t_dl_list	*var_item;

	if (state && var)
	{
		var_item = ft_dl_lstnew(var);
		if (state->var_list)
			ft_dl_addlast(state->var_list, var_item);
		else
			state->var_list = var_item;
	}
}
