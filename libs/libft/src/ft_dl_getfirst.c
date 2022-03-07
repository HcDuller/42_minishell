/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_getfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:45:32 by hde-camp          #+#    #+#             */
/*   Updated: 2022/01/31 18:52:49 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dl_list	*ft_dl_getfirst(t_dl_list *item)
{
	t_dl_list	*first;

	first = NULL;
	if (item)
	{
		first = item;
		while (first->prev)
			first = first->prev;
		return (first);
	}
	return (first);
}
