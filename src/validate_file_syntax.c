/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:56:46 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/09 18:34:25 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	validate_file_sintax(t_cmd	*cmd)
{
	if (!cmd->argv)
	{
		cmd->type = INVALID;
	}
}
