/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_freeer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:04:58 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/23 21:37:16 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_word_list(t_shstate *state)
{
	while (state->words)
		ft_dl_removeone(&state->words, free_word);
}

void	free_word(void *wrd)
{
	t_word	*ptr;

	ptr = (t_word *)wrd;
	if (ptr)
	{
		if ((ptr)->expanded)
			free((ptr)->expanded);
		free(ptr);
		ptr = NULL;
	}
}
