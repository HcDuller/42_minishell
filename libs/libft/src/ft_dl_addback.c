/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_addback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:02:00 by hcduller          #+#    #+#             */
/*   Updated: 2022/01/30 19:34:34 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_addback(t_dl_list **lst, t_dl_list *new)
{
	if (!lst || !new)
		return ;
	new->next = (*lst)->next;
	new->prev = (*lst);
	if ((*lst)->next)
		(*lst)->next->prev = new;
	(*lst)->next = new;
	*lst = new;
}
