/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:40:20 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/03 20:13:02 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_cmd(void *ptr);

void	free_cmds(t_shstate *state)
{
	while (state->cmds)
		ft_dl_removeone(&state->cmds, free_cmd);
}

static void	free_cmd(void *ptr)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)ptr;
	if (cmd)
	{
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				cmd->argv[i] = NULL;
				i++;
			}
			free(cmd->argv);
		}
		free(ptr);
	}
}
