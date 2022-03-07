/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_word_builders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:12:09 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 21:10:25 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_word	*new_sub_word(char *input);

t_dl_list	*build_sub_words(t_word **word)
{
	if (word)
	{
		if (*word)
		{
			if ((*word)->type == SIMPLE || (*word)->type == VARIABLE)
			{
				return (build_simple_sub_words(word));
			}
			else if ((*word)->type == D_QUOTED || (*word)->type == S_QUOTED)
			{
				return (build_quoted_sub_words(word));
			}
		}
	}
	return (NULL);
}

void	sub_word_list_builder(t_dl_list **list, char *input)
{
	t_dl_list	*tmp_lst;

	if (input)
	{
		if (*list)
		{
			tmp_lst = ft_dl_lstnew(new_sub_word(input));
			ft_dl_addback(list, tmp_lst);
		}
		else
		{
			*list = ft_dl_lstnew(new_sub_word(input));
		}
	}
}

t_dl_list	*build_quoted_sub_words(t_word **word)
{
	t_dl_list	*wrd_lst;
	t_word		*tmp_wrd;
	int			str_i;

	str_i = 0;
	wrd_lst = NULL;
	(*word)->start += 1;
	(*word)->size -= 2;
	while (str_i < (*word)->size)
	{
		sub_word_list_builder(&wrd_lst, (char *)((*word)->start + str_i));
		tmp_wrd = wrd_lst->content;
		if ((*word)->type == D_QUOTED)
			sub_d_quoted_delimiter(&tmp_wrd);
		else
		{
			tmp_wrd->type = SIMPLE;
			sub_s_quoted_delimiter(&tmp_wrd);
		}
		str_i += tmp_wrd->size;
	}
	return (ft_dl_getfirst(wrd_lst));
}

t_dl_list	*build_simple_sub_words(t_word **word)
{
	t_dl_list	*wrd_lst;
	t_word		*tmp_wrd;
	int			str_i;

	str_i = 0;
	wrd_lst = NULL;
	while (str_i < (*word)->size)
	{
		sub_word_list_builder(&wrd_lst, (char *)((*word)->start + str_i));
		tmp_wrd = wrd_lst->content;
		sub_simple_delimiter(&tmp_wrd);
		str_i += tmp_wrd->size;
	}
	return (ft_dl_getfirst(wrd_lst));
}

static t_word	*new_sub_word(char *input)
{
	t_word	*word;

	if (*input)
	{
		word = ft_calloc(1, sizeof(t_word));
		word->start = input;
		if ((int)*input == '$')
		{
			if (ft_isalnum((int)*(input + 1)) || *(input + 1) == '?')
				word->type = VARIABLE;
			else
				word->type = SIMPLE;
		}
		else if ((int)*input == '~')
		{
			if (!(*(input + 1)) || ft_isspace(*(input + 1)))
				word->type = VARIABLE;
			else
				word->type = SIMPLE;
		}
		else
			word->type = SIMPLE;
		return (word);
	}
	return (NULL);
}
