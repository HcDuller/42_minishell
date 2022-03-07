/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_removeone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 13:55:29 by hde-camp          #+#    #+#             */
/*   Updated: 2022/01/29 14:17:07 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstdestroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:30:53 by hcduller          #+#    #+#             */
/*   Updated: 2022/01/28 17:41:59 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_removeone(t_dl_list **lst, void (*del)(void*))
{
	t_dl_list	*temp;

	if (!(*lst))
		return ;
	temp = (*lst);
	if (temp->next)
		temp = temp->next;
	else if (temp->prev)
		temp = temp->prev;
	else
		temp = NULL;
	if (del)
		ft_dl_lstdestroy(*lst, del);
	else
		ft_dl_lstdestroy(*lst, NULL);
	*lst = temp;
}
