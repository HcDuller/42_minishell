/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:17:01 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/04 14:49:05 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_word	*start_word(char *input);
static void		build_word_list(t_shstate *state);

void	input_parser(t_shstate *state)
{
	build_word_list(state);
	expand_words(state);
	merge_words(state);
	build_cmds(state);
	eval_cmds(state);
}

static void	build_word_list(t_shstate *state)
{
	char		*input;
	t_dl_list	*w_list;
	t_word		*wrd;

	input = state->input;
	w_list = NULL;
	while (*input)
	{
		if (w_list)
		{
			ft_dl_addback(&w_list, ft_dl_lstnew(start_word(input)));
		}
		else
			w_list = ft_dl_lstnew(start_word(input));
		wrd = w_list->content;
		word_delimiter(&wrd);
		input += wrd->size;
	}
	if (w_list)
		state->words = ft_dl_getfirst(w_list);
}

static t_word	*start_word(char *input)
{
	t_word	*word;

	if (*input)
	{
		word = ft_calloc(1, sizeof(t_word));
		word->start = input;
		if ((int)*input == S_QUOTED)
			word->type = S_QUOTED;
		else if ((int)*input == D_QUOTED)
			word->type = D_QUOTED;
		else if (ft_chrinstr((char)*input, "<|>"))
			word->type = OPERATOR;
		else if (ft_isspace((char)*input))
			word->type = WHITE_SPACE;
		else
			word->type = SIMPLE;
		return (word);
	}
	return (NULL);
}
