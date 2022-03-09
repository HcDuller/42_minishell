/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_word_delimiters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:27:54 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/09 17:19:05 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sub_d_quoted_delimiter(t_word **word)
{
	char	*wrd;
	int		i;

	wrd = (char *)(*word)->start;
	i = 0;
	if (*wrd)
	{
		if (i == 0 && wrd[i] == '$')
		{
			i++;
			while (wrd[i] && !ft_isspace(wrd[i]) && wrd[i] != S_QUOTED \
					&& wrd[i] != D_QUOTED && wrd[i] != '$')
				i++;
			if (i < 2)
			{
				(*word)->type = SIMPLE;
			}
		}
		else
		{
			while (wrd[i] && wrd[i] != D_QUOTED && wrd[i] != '$')
				i++;
		}
		(*word)->size = i;
	}
}

void	sub_s_quoted_delimiter(t_word **word)
{
	char	*wrd;
	int		i;

	wrd = (char *)(*word)->start;
	i = 0;
	if (*wrd)
	{
		if (i == 0 && wrd[i] == '$')
			i++;
		while (wrd[i] && wrd[i] != S_QUOTED)
		{
			i++;
		}
		(*word)->size = i;
	}
}

void	sub_simple_delimiter(t_word **word)
{
	char	*wrd;
	int		i;

	wrd = (char *)(*word)->start;
	i = 0;
	if (*wrd)
	{
		if (i == 0 && wrd[i] == '$')
			i++;
		if (ft_isdigit(wrd[i]) || wrd[i] == '?')
		{
			i++;
		}
		else
		{
			while (wrd[i] && !ft_isspace(wrd[i]) && \
				wrd[i] != S_QUOTED && \
				wrd[i] != D_QUOTED && \
				!ft_chrinstr(wrd[i], "<|>") && \
				wrd[i] != '$')
			{
				i++;
			}
		}
		(*word)->size = i;
	}
}
