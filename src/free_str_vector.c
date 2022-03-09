/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:11:18 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/08 18:13:24 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_str_vector(char **vector)
{
	char	**ptr;
	int		p_index;

	ptr = vector;
	p_index = 0;
	if (ptr)
	{
		while (ptr[p_index])
		{
			free(ptr[p_index]);
			ptr[p_index] = NULL;
			p_index++;
		}
		free(vector);
		vector = NULL;
	}
}
