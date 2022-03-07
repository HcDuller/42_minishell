/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_word_delimiter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:13:50 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/24 19:14:17 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	differentiate_single_and_double(t_word **word, char *wrd);

void	operator_word_delimiter(t_word **word)
{
	char	*wrd;

	wrd = (char *)(*word)->start;
	(*word)->size = 1;
	if (*wrd == S_LESSTHAN || *wrd == S_GREATERTHAN)
	{
		differentiate_single_and_double(word, wrd);
	}
	else if (*wrd == PIPE)
	{
		(*word)->type = PIPE;
	}
}

static void	differentiate_single_and_double(t_word **word, char *wrd)
{
	if (*(wrd + 1) == *(wrd))
	{
		(*word)->size++;
		if (*wrd == S_LESSTHAN)
			(*word)->type = D_LESSTHAN;
		else
			(*word)->type = D_GREATERTHAN;
	}
	else
	{
		if (*wrd == S_LESSTHAN)
			(*word)->type = S_LESSTHAN;
		else
			(*word)->type = S_GREATERTHAN;
	}
}
