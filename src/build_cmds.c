/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:22:11 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/01 16:04:29 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	build_cmds(t_shstate *state)
{
	t_dl_list	*w_list;
	t_dl_list	*new_item;
	t_cmd		*temp_cmd;

	w_list = state->words;
	while (w_list)
	{
		temp_cmd = get_cmd_and_move(&w_list);
		if (temp_cmd)
		{
			new_item = ft_dl_lstnew((void *)temp_cmd);
			if (state->cmds)
			{
				ft_dl_addback(&state->cmds, new_item);
			}
			else
			{
				state->cmds = new_item;
			}
		}
	}
	state->cmds = ft_dl_getfirst(state->cmds);
}
