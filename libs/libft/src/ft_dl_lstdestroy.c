/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstdestroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:30:53 by hcduller          #+#    #+#             */
/*   Updated: 2022/02/14 18:26:53 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_lstdestroy(t_dl_list *item, void (*del)(void*))
{
	if (!item)
		return ;
	if (item->prev)
	{
		if (item->next)
		{
			item->prev->next = item->next;
			item->next->prev = item->prev;
		}
		else
			item->prev->next = NULL;
	}
	else
	{
		if (item->next)
			item->next->prev = NULL;
	}
	if (del)
		del((void *)item->content);
	free(item);
}
