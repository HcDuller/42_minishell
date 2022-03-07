/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_state_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:34:31 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/03 10:36:53 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_env_vars(t_dl_list *ptr);
static char	*str_env_var(t_variable *var);

char	**get_state_env(t_shstate *state)
{
	int			size;
	int			i;
	t_dl_list	*var_list;
	char		**envlist;

	var_list = ft_dl_getfirst(state->var_list);
	size = count_env_vars(var_list);
	envlist = ft_calloc(size + 1, sizeof(char **));
	i = 0;
	while (var_list)
	{
		if (var_list->content)
		{
			if (((t_variable *)var_list->content)->exported)
			{
				envlist[i] = str_env_var((t_variable *)var_list->content);
				i++;
			}
		}
		var_list = var_list->next;
	}
	return (envlist);
}

static	char	*str_env_var(t_variable	*var)
{
	char	*var_as_str;
	int		k_s;
	int		v_s;

	var_as_str = NULL;
	if (var->exported)
	{
		k_s = ft_strlen(var->key);
		v_s = ft_strlen(var->value);
		var_as_str = ft_calloc(k_s + v_s + 2, sizeof(char));
		ft_memmove(var_as_str, var->key, k_s);
		ft_memmove(var_as_str + k_s, "=", 1);
		ft_memmove(var_as_str + k_s + 1, var->value, v_s);
	}
	return (var_as_str);
}

static	int	count_env_vars(t_dl_list	*ptr)
{
	int			size;
	t_dl_list	*dl_list;

	size = 0;
	dl_list = ft_dl_getfirst(ptr);
	while (dl_list)
	{
		if (dl_list->content)
		{
			if (((t_variable *)dl_list->content)->exported)
				size++;
		}
		dl_list = dl_list->next;
	}
	return (size);
}
