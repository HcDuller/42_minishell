/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_word_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:51:13 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/03 10:55:10 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_all_words(t_shstate *state)
{
	t_dl_list	*w_item;
	char		*ptr;
	int			len;

	if (state->words)
	{
		w_item = state->words;
		while (w_item)
		{
			ptr = (char *)((t_word *)w_item->content)->start;
			len = ((t_word *)w_item->content)->size;
			write(STDOUT_FILENO, ptr, len);
			write(STDOUT_FILENO, "\n", 1);
			w_item = w_item->next;
		}
	}
}

void	print_all_exp_words(t_shstate *state)
{
	t_dl_list	*w_item;
	char		*ptr;
	int			len;

	if (state->words)
	{
		w_item = state->words;
		while (w_item)
		{
			if (((t_word *)w_item->content)->expanded)
			{
				ptr = (char *)((t_word *)w_item->content)->expanded;
				len = ((t_word *)w_item->content)->expanded_size;
				write(STDOUT_FILENO, ptr, len);
			}
			else
			{
				ptr = (char *)((t_word *)w_item->content)->start;
				len = ((t_word *)w_item->content)->expanded_size;
				write(STDOUT_FILENO, ptr, len);
			}
			write(STDOUT_FILENO, "\n", 1);
			w_item = w_item->next;
		}
	}
}

void	print_all_cmds(t_shstate *state)
{
	t_dl_list	*cmd_item;

	if (state->cmds)
	{
		cmd_item = state->cmds;
		while (cmd_item)
		{
			if (((t_cmd *)cmd_item->content)->argv[0])
			{
				printf("%s\n", ((t_cmd *)cmd_item->content)->argv[0]);
			}
			cmd_item = cmd_item->next;
		}
	}
}
