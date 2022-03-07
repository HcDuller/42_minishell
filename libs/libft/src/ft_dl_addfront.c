/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_addfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:02:00 by hcduller          #+#    #+#             */
/*   Updated: 2022/01/31 18:47:33 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_addfront(t_dl_list **lst, t_dl_list *new)
{
	if (!lst || !new)
		return ;
	if ((*lst)->prev)
		(*lst)->prev->next = new;
	new->prev = (*lst)->prev;
	new->next = (*lst);
	(*lst)->prev = new;
	*lst = new;
}
