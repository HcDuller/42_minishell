/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:19:17 by snovaes           #+#    #+#             */
/*   Updated: 2022/03/09 18:35:25 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_welcome_msg(void)
{
	write(STDERR_FILENO, "\033[1;33m", 7);
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
	write(STDERR_FILENO, "\033[0m", 4);
}