/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_addlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:02:00 by hcduller          #+#    #+#             */
/*   Updated: 2022/01/28 18:23:53 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_addlast(t_dl_list *item, t_dl_list *new)
{
	if (!item || !new)
		return ;
	while (item->next)
		item = item->next;
	item->next = new;
	new->prev = item;
}
