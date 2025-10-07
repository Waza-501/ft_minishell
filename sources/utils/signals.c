/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/27 20:35:45 by owen          #+#    #+#                 */
/*   Updated: 2025/10/07 11:17:48 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief Ignore the SIGQUIT signal (Ctrl+\) in the current process.
 *
 * Sets the handler for SIGQUIT to SIG_IGN, so the process will not terminate
 * or dump core when receiving this signal.
 */
void	trap_sigquit(void)
{
	struct sigaction	ms;

	ft_memset(&ms, 0, sizeof(ms));
	ms.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ms, NULL);
}

/**
 * @brief Signal handler for SIGINT in interactive mode.
 *
 * Prints a newline, clears the current input line, and redisplays the prompt.
 * Used to provide a clean user experience when Ctrl+C is pressed.
 *
 * @param signal The signal number (unused).
 */
void	reset_line(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Signal handler that moves the cursor to a new line.
 *
 * Used in non-interactive mode to handle signals without clearing input.
 *
 * @param signal The signal number (unused).
 */
void	put_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

/**
 * @brief Set up signal handlers for interactive shell mode.
 *
 * Ignores SIGQUIT and sets SIGINT to clear the input line
 * and redisplay the prompt.
 */
void	set_signals_interactive(void)
{
	struct sigaction	ms;

	trap_sigquit();
	ft_memset(&ms, 0, sizeof(ms));
	ms.sa_handler = &reset_line;
	sigaction(SIGINT, &ms, NULL);
}

/**
 * @brief Set up signal handlers for non-interactive shell mode.
 *
 * Sets both SIGINT and SIGQUIT to simply move to a new line.
 */
void	set_signals_noninteractive(void)
{
	struct sigaction	ms;

	ft_memset(&ms, 0, sizeof(ms));
	ms.sa_handler = &put_newline;
	sigaction(SIGINT, &ms, NULL);
	sigaction(SIGQUIT, &ms, NULL);
}
