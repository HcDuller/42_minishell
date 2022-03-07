/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_addfirst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:02:00 by hcduller          #+#    #+#             */
/*   Updated: 2022/01/28 18:24:24 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_addfirst(t_dl_list *item, t_dl_list *new)
{
	if (!item || !new)
		return ;
	while (item->prev)
		item = item->prev;
	new->next = item;
	item->prev = new;
}
