/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:56:46 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/08 18:24:09 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	validate_file_sintax(t_cmd	*cmd)
{
	if (!cmd->argv)
	{
		cmd->type = INVALID;
		//write(STDERR_FILENO, "minishell: syntax error near unexpected token\n", 46);
	}
}
