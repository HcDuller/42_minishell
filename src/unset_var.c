/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:41:14 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/25 15:57:10 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset_var(t_dl_list *var_item)
{
	if (var_item)
	{
		ft_dl_removeone(&var_item, delete_var);
	}
}

void	unset_all_var(t_shstate *state)
{
	state->var_list = ft_dl_getfirst(state->var_list);
	if (state->var_list)
	{
		while (state->var_list)
		{
			ft_dl_removeone(&state->var_list, delete_var);
		}
	}
}
