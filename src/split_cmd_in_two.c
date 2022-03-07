/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_in-two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:42:17 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/05 20:46:29 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		argv_size(char **argv);
static void		argv_free(char **argv);

void	split_cmd_in_two(t_dl_list	*cmd_list)
{
	t_cmd	*cur_cmd;
	t_cmd	*nxt_cmd;
	char	**tmp_argv;
	int		i;

	cur_cmd = cmd_list->content;
	nxt_cmd = new_cmd();
	nxt_cmd->l_operator = cur_cmd->l_operator;
	nxt_cmd->r_operator = cur_cmd->r_operator;
	cur_cmd->r_operator = cur_cmd->l_operator;
	cur_cmd->l_operator = UNKNOWN;
	tmp_argv = cur_cmd->argv;
	nxt_cmd->argv = ft_calloc(2, sizeof(char *));
	cur_cmd->argv = ft_calloc(argv_size(tmp_argv), sizeof(char *));
	nxt_cmd->argv[0] = ft_strdup(tmp_argv[0]);
	i = 1;
	while (i < argv_size(tmp_argv))
	{
		cur_cmd->argv[i - 1] = ft_strdup(tmp_argv[i]);
		i++;
	}
	ft_dl_addback(&cmd_list, ft_dl_lstnew(nxt_cmd));
	argv_free(tmp_argv);
}

static	int	argv_size(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

static	void	argv_free(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}
