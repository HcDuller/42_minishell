/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:24:50 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 20:53:19 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_expandable(t_word *wrd);
static void	expand_word(t_shstate *state, t_dl_list **sub_words, t_word **wrd);
static int	get_word_final_size(t_dl_list *sub_words);
static char	*concat_sub_words(t_dl_list *sub_words);

void	expand_words(t_shstate *state)
{
	t_dl_list	*sub_words;
	t_dl_list	*w_list;
	t_word		*ptr;

	w_list = ft_dl_getfirst(state->words);
	if (w_list)
	{
		while (w_list)
		{
			ptr = (t_word *)w_list->content;
			sub_words = NULL;
			if (is_expandable(ptr))
			{
				expand_word(state, &sub_words, &ptr);
			}
			else
			{
				ptr->expanded = ft_calloc(ptr->size + 1, sizeof(char));
				ptr->expanded_size = ptr->size;
				ft_memmove(ptr->expanded, ptr->start, ptr->size);
			}
			w_list = w_list->next;
		}
	}
}

static void	expand_word(t_shstate *state, t_dl_list **sub_words, t_word **wrd)
{
	*sub_words = build_sub_words(wrd);
	expand_sub_words(state, *sub_words);
	(*wrd)->expanded = concat_sub_words(*sub_words);
	(*wrd)->expanded_size = ft_strlen((*wrd)->expanded);
	while (*sub_words)
		ft_dl_removeone(sub_words, free_word);
}

static int	is_expandable(t_word *wrd)
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

static int	get_word_final_size(t_dl_list *sub_words)
{
	t_dl_list	*w_list;
	t_word		*wrd;
	int			size;

	size = 0;
	w_list = sub_words;
	while (w_list)
	{
		wrd = w_list->content;
		size += wrd->size;
		w_list = w_list->next;
	}
	return (size);
}

static char	*concat_sub_words(t_dl_list *sub_words)
{
	t_dl_list	*w_list;
	t_word		*wrd;
	int			final_size;
	int			final_index;
	char		*final;

	final_size = get_word_final_size(sub_words);
	w_list = sub_words;
	final_index = 0;
	final = (char *)ft_calloc(final_size + 1, sizeof(char));
	while (w_list)
	{
		wrd = w_list->content;
		if (wrd->type == VARIABLE)
			ft_memmove(final + final_index, wrd->expanded, wrd->size);
		else
			ft_memmove(final + final_index, wrd->start, wrd->size);
		final_index += wrd->size;
		w_list = w_list->next;
	}
	return (final);
}
