/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:42:04 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/08 18:10:30 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**load_paths(t_shstate *state)
{
	char	**temp_paths;
	char	**final_paths;
	int		size;
	int		i;

	temp_paths = ft_split(get_var_value(state, "PATH"), ':');
	final_paths = NULL;
	if (temp_paths)
	{
		size = 0;
		while (temp_paths[size])
			size++;
		final_paths = ft_calloc(size + 1, sizeof(char **));
		i = 0;
		while (temp_paths[i])
		{
			(final_paths)[i] = ft_strjoin(temp_paths[i], "/");
			free(temp_paths[i]);
			i++;
		}
		free(temp_paths);
	}
	return (final_paths);
}
