/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/26 12:52:14 by haile         #+#    #+#                 */
/*   Updated: 2025/11/26 12:53:51 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

/**
 * @brief Reset signals to default for child processes.
 *
 * Called in child process after fork() but before exec() to ensure
 * child processes can be killed normally by SIGINT/SIGQUIT.
 */

void	reset_signals_for_child(void)
{
	struct sigaction	ms;

	ft_memset(&ms, 0, sizeof(ms));
	ms.sa_handler = SIG_DFL;
	sigaction(SIGINT, &ms, NULL);
	sigaction(SIGQUIT, &ms, NULL);
}

void	set_signals_parent_execution(void)
{
	struct sigaction	ms;

	ft_memset(&ms, 0, sizeof(ms));
	ms.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ms, NULL);
	sigaction(SIGQUIT, &ms, NULL);
}

void	restore_signals_interactive(void)
{
	set_signals_noninteractive();
}
