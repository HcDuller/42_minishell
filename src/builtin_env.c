/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:19:11 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/07 12:43:46 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_env(t_shstate *state)
{
	t_dl_list	*var_item;
	t_variable	*var;

	var_item = ft_dl_getfirst(state->var_list);
	while (var_item)
	{
		var = ((t_variable *)var_item->content);
		if (var->value && var->exported)
		{
			write(STDOUT_FILENO, var->key,
				ft_strlen(var->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, var->value,
				ft_strlen(var->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		var_item = var_item->next;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
