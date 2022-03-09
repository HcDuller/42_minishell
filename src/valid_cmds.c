/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 11:04:36 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/09 16:57:32 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	all_cmds_are_valid(t_dl_list	*cmds)
{
	t_dl_list	*list;
	t_cmd		*cmd;

	list = cmds;
	while (list)
	{
		cmd = (t_cmd *)list->content;
		if (cmd)
		{
			if (cmd->type == INVALID)
				return (0);
		}
		list = list->next;
	}
	return (1);
}

int	cmd_list_should_run(t_dl_list	*cmds)
{
	t_dl_list	*list;
	t_cmd		*cmd;

	list = cmds;
	while (list)
	{
		cmd = (t_cmd *)list->content;
		if (cmd)
		{
			if (cmd->type == UNEXPECTED_TOKEN)
				return (0);
		}
		list = list->next;
	}
	return (1);
}