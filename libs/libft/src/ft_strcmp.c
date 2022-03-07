/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:13:33 by hde-camp          #+#    #+#             */
/*   Updated: 2022/01/31 19:18:16 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] && s2[i])
		{
			if (s1[i] != s2[i])
				return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
		}			
		else if (s1[i] && !s2[i])
			return ((unsigned char)s1[i]);
		else if (!s1[i] && s2[i])
			return (-1 * ((unsigned char)s2[i]));
		i++;
	}
	return (0);
}
