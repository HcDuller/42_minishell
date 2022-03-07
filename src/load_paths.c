/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:42:04 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/24 16:54:20 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	load_paths(t_shstate *state)
{
	char	**temp_paths;
	int		size;
	int		i;

	temp_paths = ft_split(getenv("PATH"), ':');
	size = 0;
	while (temp_paths[size])
		size++;
	state->paths = ft_calloc(size + 1, sizeof(char **));
	i = 0;
	while (temp_paths[i])
	{
		(state->paths)[i] = ft_strjoin(temp_paths[i], "/");
		free(temp_paths[i]);
		i++;
	}
	free(temp_paths);
}
