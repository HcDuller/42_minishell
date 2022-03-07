/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:29:07 by hde-camp          #+#    #+#             */
/*   Updated: 2022/01/29 15:08:58 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dl_list	*ft_dl_lstnew(void *content)
{
	t_dl_list	*p;

	p = malloc(sizeof(t_dl_list));
	if (p)
	{
		p->content = content;
		p->next = NULL;
		p->prev = NULL;
	}
	return (p);
}
