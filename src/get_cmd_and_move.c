/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_and_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:17:10 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/09 16:39:19 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		count_cmd_words(t_dl_list *wrds);
static int		is_operator(t_word *wrd);
static void		dup_argv_into_cmd(t_dl_list **words, t_cmd	*cmd, int argc);

t_cmd	*get_cmd_and_move(t_dl_list **words)
{
	t_cmd	*cmd;
	int		args_size;

	cmd = NULL;
	if ((*words))
	{
		cmd = new_cmd();
		if (is_operator((t_word *)(*words)->content))
		{
			cmd->l_operator = ((t_word *)(*words)->content)->type;
			(*words) = (*words)->next;
		}
		args_size = count_cmd_words((*words));
		if (args_size > 0)
			cmd->argv = (char **)ft_calloc(args_size + 1, sizeof (char **));
		dup_argv_into_cmd(words, cmd, args_size);
		if (*words)
		{
			if (is_operator((t_word *)(*words)->content))
			{
				cmd->r_operator = ((t_word *)(*words)->content)->type;
			}
		}
	}
	return (cmd);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	new->write = STDOUT_FILENO;
	new->read = STDIN_FILENO;
	new->err_msg = NULL;
	new->argv = NULL;
	return (new);
}

static int	count_cmd_words(t_dl_list *wrds)
{
	int	wrd_counter;

	wrd_counter = 0;
	while (wrds)
	{
		if (is_operator(wrds->content))
			break ;
		wrd_counter += 1;
		wrds = wrds->next;
	}
	return (wrd_counter);
}

static int	is_operator(t_word *wrd)
{
	enum e_word_type	type;

	if (wrd)
	{
		type = wrd->type;
		if (type == S_LESSTHAN || \
			type == S_GREATERTHAN || \
			type == D_LESSTHAN || \
			type == D_GREATERTHAN || \
			type == PIPE)
			return (1);
	}
	return (0);
}

static void	dup_argv_into_cmd(t_dl_list **words, t_cmd	*cmd, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (((t_word *)(*words)->content)->type != WHITE_SPACE)
		{
			cmd->argv[i] = ft_strdup(((t_word *)(*words)->content)->expanded);
			i++;
		}
		(*words) = (*words)->next;
	}
}
