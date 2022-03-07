/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_destroyall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 13:48:44 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/07 13:30:53 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dl_destroyall(t_dl_list *item, void (*del)(void*))
{
	void	*fnc;

	if (!(item))
		return ;
	if (del)
		fnc = del;
	else
		fnc = NULL;
	while (item)
		ft_dl_removeone(&item, fnc);
}
