/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_sub_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 00:50:22 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/05 19:11:12 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_tilde_variable(t_shstate *state, t_word *wrd)
{
	char	*var_name;
	char	*var_value;

	var_value = NULL;
	var_name = ft_calloc(5, sizeof(char));
	ft_strlcpy(var_name, "HOME", 5);
	var_value = (char *)get_var_value(state, var_name);
	if (var_value)
		wrd->expanded = ft_strdup(var_value);
	else
		wrd->expanded = NULL;
	free(var_name);
	wrd->size = ft_strlen(wrd->expanded);
}

void	expand_sub_varaible_word(t_shstate *state, t_word *wrd)
{
	char	*var_name;
	char	*var_value;

	if (wrd->size == 1)
		expand_tilde_variable(state, wrd);
	else
	{
		var_name = ft_calloc(wrd->size + 1, sizeof(char));
		ft_memmove(var_name, wrd->start + 1, wrd->size - 1);
		var_value = (char *)get_var_value(state, var_name);
		if (var_value)
			wrd->expanded = ft_strdup(var_value);
		else
			wrd->expanded = NULL;
		free(var_name);
		wrd->size = ft_strlen(wrd->expanded);
	}
}

void	expand_sub_words(t_shstate *state, t_dl_list *sub_words)
{
	t_word	*wrd;

	while (sub_words)
	{
		wrd = (t_word *)sub_words->content;
		if (wrd->type == VARIABLE)
		{
			expand_sub_varaible_word(state, wrd);
		}
		else if (wrd->type == SIMPLE)
		{
			wrd->expanded = ft_calloc(wrd->size + 1, sizeof(char));
			ft_memmove(wrd->expanded, wrd->start, wrd->size);
			wrd->expanded_size = wrd->size;
		}
		sub_words = sub_words->next;
	}
}
