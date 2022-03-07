/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsign_word_delimiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:08:19 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/03 17:19:28 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dsign_word_delimiter(t_word **word)
{
	char	*wrd;

	wrd = (*word)->start;
	if (*wrd)
	{
		wrd++;
		(*word)->size++;
		while (*wrd && !ft_isspace(*wrd) && \
				*wrd != S_QUOTED && *wrd != D_QUOTED && \
				*wrd != D_SIGN && *wrd != '|')
		{
			(*word)->size++;
			wrd++;
		}
	}
}
