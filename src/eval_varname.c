/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_varname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:33:34 by snovaes           #+#    #+#             */
/*   Updated: 2022/02/25 19:52:35 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	eval_varname(char *name)
{
	if (name)
	{
		if (ft_isalpha((int)*name))
		{
			name++;
			while (*name)
			{
				if (!(ft_isalnum((int)*name)) && !(*name == '_'))
					return (0);
				name++;
			}
		}
		return (1);
	}
	return (0);
}

int	eval_var_atribution(char *name)
{
	char	*ptr;
	char	*var_name;
	int		bool;

	ptr = ft_strchr((const char *)name, '=');
	if (ptr)
	{
		var_name = ft_calloc((ptr - name) + 1, sizeof(char));
		ft_memmove(var_name, name, (ptr - name));
		bool = eval_varname(var_name);
		free(var_name);
		return (bool);
	}
	return (0);
}
