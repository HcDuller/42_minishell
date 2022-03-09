/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:19:17 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/09 20:42:28 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_welcome_msg(void)
{
	ft_putstr_fd(YELLOW, STDERR_FILENO);
	ft_putstr_fd("                                        \n", 2);
	ft_putstr_fd("               ▄█████████▄              \n", 2);
	ft_putstr_fd("            ▄███████████████▄           \n", 2);
	ft_putstr_fd("         ██████▀   ██   ▀███████        \n", 2);
	ft_putstr_fd("      ███   ▀███   ██   ███▀   ███      \n", 2);
	ft_putstr_fd("     ██████   ██   ██   ██   ██████     \n", 2);
	ft_putstr_fd("     ██   ██   ██  ██  ██   ██   ██     \n", 2);
	ft_putstr_fd("    ███    ██  ██  ██  ██  ██    ███    \n", 2);
	ft_putstr_fd("    ██ ██   ██  █  ██  █  ██   ██ ██    \n", 2);
	ft_putstr_fd("    ██  ███  ██ ██ ██ ██ ██  ███  ██    \n", 2);
	ft_putstr_fd("    ██    ██  ██ █ ██ █ ██  ██    ██    \n", 2);
	ft_putstr_fd("    ████▄   ██ █  █  █  █ ██   ▄████    \n", 2);
	ft_putstr_fd("       ████   █          █   ████       \n", 2);
	ft_putstr_fd("          ██                ██          \n", 2);
	ft_putstr_fd("          ████████▄  ▄████████          \n", 2);
	ft_putstr_fd("                  ▀██▀                  \n", 2);
	ft_putstr_fd("           _       _     _          _ _ \n", 2);
	ft_putstr_fd(" _ __ ___ (_)_ __ (_)___| |__   ___| | |\n", 2);
	ft_putstr_fd("| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n", 2);
	ft_putstr_fd("| | | | | | | | | | \\__ \\ | | |  __/ | |\n", 2);
	ft_putstr_fd("|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\n", 2);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

void	print_error(void)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `newline'", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
