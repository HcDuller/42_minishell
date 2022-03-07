/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_crud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:18:30 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/03 18:54:31 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_variable	*create_var(const char *key, const char *value)
{
	t_variable	*new_var;

	new_var = NULL;
	if (key)
	{
		new_var = (t_variable *)ft_calloc(1, sizeof(t_variable));
		new_var->key = ft_strdup(key);
		if (value)
			new_var->value = ft_strdup(value);
	}
	return (new_var);
}

void	delete_var(void *var)
{
	t_variable	*ptr;

	ptr = (t_variable *)var;
	if (ptr)
	{
		if ((ptr)->key)
			free((ptr)->key);
		if ((ptr)->value)
			free((ptr)->value);
		free(ptr);
		ptr = NULL;
	}
}

void	update_var(t_variable *var, const char *new_value)
{
	if (var->value)
	{
		free(var->value);
		var->value = ft_strdup(new_value);
	}
}
