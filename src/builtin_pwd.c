/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:00:08 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/05 21:34:10 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_current_directory(void);

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = get_current_directory();
	if (cwd)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		free(cwd);
	}
}

static char	*get_current_directory(void)
{
	return (getcwd(NULL, 0));
}
