/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:06:58 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/07 16:54:44 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcduller <hcduller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:50:28 by hcduller          #+#    #+#             */
/*   Updated: 2021/06/03 17:26:59 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static	unsigned long	r_len(unsigned long n);
static	unsigned long	mod(unsigned long n);

char	*ft_litoa(unsigned long n)
{
	unsigned long	len;
	unsigned long	i;
	char			*p;

	len = r_len(n);
	i = len;
	p = ft_calloc(i + 1, 1);
	if (!p)
		return (NULL);
	while (i > 0)
	{
		p[--i] = mod(n % 10) + 48;
		if (!(n / 10 == 0))
			n = n / 10;
	}
	return (p);
}

unsigned long	r_len(unsigned long n)
{
	unsigned long	i;

	i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

unsigned long	mod(unsigned long n)
{
	return (n);
}
