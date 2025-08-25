/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:45 by owen          #+#    #+#                 */
/*   Updated: 2025/07/28 14:55:38 by owen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	trap_sigquit()
{
	struct sigaction	ms;

	ft_memset(&ms, 0, sizeof(ms));
	ms.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ms, NULL);
}

void	reset_line(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	put_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	set_signals_interactive(void)
{
	struct sigaction	ms;

	trap_sigquit();
	ft_memset(&ms, 0, sizeof(ms));
	ms.sa_handler = &reset_line;
	sigaction(SIGINT, &ms, NULL);
}

void	set_signals_noninteractive(void)
{
	struct sigaction	ms;

	ft_memset(&ms, 0, sizeof(ms));
	ms.sa_handler = &put_newline;
	sigaction(SIGINT, &ms, NULL);
	sigaction(SIGQUIT, &ms, NULL);
}
