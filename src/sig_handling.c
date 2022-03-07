/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:12:09 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/04 18:46:20 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	shell_handler(int sig, siginfo_t *info, void *ucontext);
void		child_handler2(int sig, siginfo_t *info, void *ucontext);

void	set_shell_handlers(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigaction(SIGINT, NULL, &sig_int);
	sig_int.sa_flags = SA_SIGINFO;
	sig_int.sa_sigaction = shell_handler;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, NULL, &sig_quit);
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	set_child_handlers(int cpid)
{
	if (cpid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	shell_handler(int sig, siginfo_t *info, void *ucontext)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
	(void)info;
	(void)ucontext;
}
