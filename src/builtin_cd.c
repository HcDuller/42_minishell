/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:24:20 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/09 17:34:55 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	int	extra_args(t_cmd	*cmd);
static	int	argv_size(char **argv);
static	void	ft_chdir(t_shstate *state, const char *new_dir);

void	builtin_cd(t_shstate *state, t_cmd	*cmd)
{
	char	*new_dir;
	int		argv_s;

	argv_s = argv_size(cmd->argv);
	new_dir = NULL;
	if (argv_s >= 3)
		extra_args(cmd);
	if (argv_s < 3 && argv_s > 0)
	{
		if (argv_s == 1)
			new_dir = (char *)get_var_value(state, "HOME");
		else if (argv_s == 2 && !ft_strcmp(cmd->argv[1], "~"))
			new_dir = (char *)get_var_value(state, "HOME");
		else if (argv_s == 2 && !ft_strcmp(cmd->argv[1], "-"))
			new_dir = (char *)get_var_value(state, "OLDPWD");
		else
			new_dir = cmd->argv[1];
		if (new_dir)
			ft_chdir(state, new_dir);
	}
}

static int	extra_args(t_cmd	*cmd)
{
	if (cmd->argv[2])
	{
		write(STDERR_FILENO, "\033[31m", 5);
        write(STDERR_FILENO, "CD: too many arguments\n", 24);
        write(STDERR_FILENO, "\033[0m", 4);
		return (1);
	}
	return (0);
}

static	int	argv_size(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

static	void	ft_chdir(t_shstate *state, const char *new_dir)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(new_dir) == 0)
	{
		set_var(state, "OLDPWD", old_pwd);
		pwd = getcwd(NULL, 0);
		set_var(state, "PWD", pwd);
		free(old_pwd);
		free(pwd);
	}
	else
	{
		perror("cd");
		set_var(state, "?", "1");
		free(old_pwd);
	}
}
