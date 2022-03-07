/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:24:48 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/24 16:53:53 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_file(char	*filename, int print_errors)
{
	struct stat	buf;

	if (stat(filename, &buf) == -1)
	{
		if (print_errors)
			perror("Error: ");
		return (0);
	}
	return (1);
}

int	check_relative_file(t_cmd	*cmd, char	**paths)
{
	char	*joined;
	int		p_i;

	p_i = 0;
	while (paths[p_i])
	{
		joined = ft_strjoin(paths[p_i], cmd->argv[0]);
		if (joined)
		{
			if (check_file(joined, 0))
			{
				free(cmd->argv[0]);
				cmd->argv[0] = joined;
				return (1);
			}
			else
			{
				free(joined);
			}
		}
		p_i++;
	}
	return (0);
}
