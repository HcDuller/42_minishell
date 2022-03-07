/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 20:52:08 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/03 18:58:29 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(t_shstate *state)
{
	t_dl_list	*var_item;
	char		**def_environment;
	int			env_index;

	env_index = 0;
	def_environment = __environ;
	while (def_environment[env_index])
	{
		if (def_environment[env_index])
			printf("%s\n", def_environment[env_index]);
		env_index++;
	}
	var_item = ft_dl_getfirst(state->var_list);
	while (var_item)
	{
		if (((t_variable *)var_item->content)->value)
		{
			printf("%s=", ((t_variable *)var_item->content)->key);
			printf("%s\n", ((t_variable *)var_item->content)->value);
		}
		var_item = var_item->next;
	}
}
