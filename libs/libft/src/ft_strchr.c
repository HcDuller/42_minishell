/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:28:14 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/07 13:33:11 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*r;

	r = (char *)s;
	while (*r)
	{
		if (*r == (char)c)
			return (r);
		r++;
		if (*r == (char)c)
			return (r);
		if (!*r)
			return (0);
	}
	if (!*r && (char)c == 0)
		return (r);
	return (0);
}
