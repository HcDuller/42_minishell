/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:53:47 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/07 10:32:53 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**split_in_two(char *str)
{
	char	**new_strs;
	char	*eq_sign;

	new_strs = ft_calloc(3, sizeof(char **));
	eq_sign = ft_strchr(str, '=');
	if (eq_sign)
	{
		*eq_sign = 0;
		new_strs[0] = ft_strdup(str);
		new_strs[1] = ft_strdup(eq_sign + 1);
	}
	else
	{
		new_strs[0] = ft_strdup(str);
		new_strs[1] = NULL;
	}
	return (new_strs);
}
