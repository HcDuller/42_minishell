/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:22:24 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 16:58:19 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	merge_word_to_next(t_dl_list **list);
static void	remove_whitespaces(t_shstate *state);
static int	is_joinable(t_word *wrd);

void	merge_words(t_shstate *state)
{
	t_dl_list	**list;

	list = &state->words;
	while ((*list)->next)
	{
		if (is_joinable((*list)->content))
		{
			if ((*list)->next)
			{
				if (is_joinable((*list)->next->content))
					merge_word_to_next(list);
				else
					(*list) = (*list)->next;
			}
			else
				(*list) = (*list)->next;
		}
		else
			(*list) = (*list)->next;
	}
	state->words = ft_dl_getfirst(state->words);
	remove_whitespaces(state);
}

static void	remove_whitespaces(t_shstate *state)
{
	t_dl_list	*list;
	t_dl_list	*temp;

	list = state->words;
	while (list)
	{
		if (((t_word *)list->content)->type == WHITE_SPACE)
		{
			ft_dl_removeone(&list, free_word);
		}
		else
		{
			temp = list;
			list = list->next;
		}
	}
	state->words = ft_dl_getfirst(temp);
}

static void	merge_word_to_next(t_dl_list **list)
{
	t_word		*new_wrd;
	t_word		*pieces[2];

	new_wrd = ft_calloc(1, sizeof(t_word));
	pieces[0] = (*list)->content;
	pieces[1] = (*list)->next->content;
	new_wrd->type = SIMPLE;
	new_wrd->expanded_size = pieces[0]->expanded_size;
	new_wrd->expanded_size += pieces[1]->expanded_size;
	new_wrd->expanded = ft_calloc(new_wrd->expanded_size + 1, sizeof(char));
	ft_memmove(new_wrd->expanded, \
			pieces[0]->expanded, pieces[0]->expanded_size);
	ft_memmove(new_wrd->expanded + pieces[0]->expanded_size, \
			pieces[1]->expanded, pieces[1]->expanded_size);
	free_word((void *)pieces[0]);
	free_word((void *)pieces[1]);
	(*list)->next->content = new_wrd;
	ft_dl_removeone(list, NULL);
}

static int	is_joinable(t_word *wrd)
{
	if (wrd->type != WHITE_SPACE \
		&& wrd->type != PIPE \
		&& wrd->type != D_LESSTHAN \
		&& wrd->type != S_LESSTHAN \
		&& wrd->type != D_GREATERTHAN \
		&& wrd->type != S_GREATERTHAN)
		return (1);
	return (0);
}
