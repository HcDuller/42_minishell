/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:33:43 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/02 16:22:30 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_cmd_input(t_dl_list	*current)
{
	int			fd;
	t_dl_list	*tmp_lst;
	t_cmd		*nxt_tmp;
	t_cmd		*cur_cmd;

	fd = -1;
	nxt_tmp = (t_cmd *)current->content;
	cur_cmd = (t_cmd *)current->content;
	tmp_lst = current;
	if (tmp_lst->next)
		nxt_tmp = (t_cmd *)current->next->content;
	while (nxt_tmp->l_operator != PIPE)
	{
		if (nxt_tmp->l_operator == S_LESSTHAN \
			|| nxt_tmp->l_operator == D_LESSTHAN)
			fd = nxt_tmp->read;
		tmp_lst = tmp_lst->next;
		if (tmp_lst)
			nxt_tmp = (t_cmd *)tmp_lst->content;
		else
			break ;
	}
	if (fd != -1)
		cur_cmd->read = fd;
}

void	set_cmd_output(t_dl_list	*current)
{
	int			fd;
	t_dl_list	*tmp_lst;
	t_cmd		*nxt_cmd;
	t_cmd		*cur_cmd;

	fd = -1;
	if (current->next)
	{
		nxt_cmd = (t_cmd *)current->next->content;
		cur_cmd = (t_cmd *)current->content;
		tmp_lst = current;
		while (nxt_cmd->l_operator != PIPE)
		{
			if (nxt_cmd->l_operator == S_GREATERTHAN \
			|| nxt_cmd->l_operator == D_GREATERTHAN)
				fd = nxt_cmd->write;
			tmp_lst = tmp_lst->next;
			if (tmp_lst)
				nxt_cmd = (t_cmd *)tmp_lst->content;
			else
				break ;
		}
		if (fd != -1)
			cur_cmd->write = fd;
	}
}
