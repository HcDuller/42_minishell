/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:37:29 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 21:11:52 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	simple_word_delimiter(t_word **word);
static void	dquoted_word_delimiter(t_word **word);
static void	squoted_word_delimiter(t_word **word);
static void	space_word_delimiter(t_word **word);

void	word_delimiter(t_word **word)
{
	if (*word)
	{
		if ((*word)->type == S_QUOTED)
			squoted_word_delimiter(word);
		else if ((*word)->type == D_QUOTED)
			dquoted_word_delimiter(word);
		else if ((*word)->type == OPERATOR)
			operator_word_delimiter(word);
		else if ((*word)->type == SIMPLE)
			simple_word_delimiter(word);
		else
			space_word_delimiter(word);
	}
}

static void	simple_word_delimiter(t_word **word)
{
	char	*wrd;

	wrd = (char *)(*word)->start;
	if (*wrd)
	{
		while (*wrd && !ft_isspace(*wrd) && \
				*wrd != S_QUOTED && \
				*wrd != D_QUOTED && \
				!ft_chrinstr((char)*wrd, "<|>"))
		{
			(*word)->size++;
			wrd++;
		}
	}
}

static void	dquoted_word_delimiter(t_word **word)
{
	char	*wrd;
	int		q_count;

	wrd = (char *)(*word)->start;
	if (*wrd)
	{
		q_count = 0;
		while (*wrd && q_count < 2)
		{
			if ((int)*wrd == D_QUOTED)
				q_count++;
			(*word)->size++;
			wrd++;
		}
	}
}

static void	squoted_word_delimiter(t_word **word)
{
	char	*wrd;
	int		q_count;

	wrd = (char *)(*word)->start;
	if (*wrd)
	{
		q_count = 0;
		while (*wrd && q_count < 2)
		{
			if ((int)*wrd == S_QUOTED)
				q_count++;
			(*word)->size++;
			wrd++;
		}
	}
}

static void	space_word_delimiter(t_word **word)
{
	char	*wrd;

	wrd = (char *)(*word)->start;
	if (*wrd)
	{
		while (*wrd && ft_isspace((char)*wrd))
		{
			(*word)->size++;
			wrd++;
		}
	}
}
