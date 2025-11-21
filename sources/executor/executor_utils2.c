/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:23:44 by haile         #+#    #+#                 */
/*   Updated: 2025/11/21 15:11:56 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "redirect.h"

void	ft_exit_exec(t_data *data, t_shell *shell, int code)
{
	if (shell)
		cleanup_shell(shell);
	if (data)
		free_data(data);
	exit(code);
}

int	try_execute_path(char *tmp, t_commands *cmd, t_shell *sh, char **path)
{
	if (access(tmp, X_OK) == 0)
	{
		execve(tmp, cmd->args, sh->env);
		perror("execve");
		ft_free_arr(path);
		free(tmp);
		ft_exit_exec(sh->data, sh, 126);
	}
	return (0);
}

char	*build_full_path(char *dir, char *cmd, char **path, t_shell *sh)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
	{
		ft_free_arr(path);
		ft_exit_exec(sh->data, sh, 1);
	}
	full_path = ft_strjoin_free(tmp, cmd);
	if (!full_path)
	{
		ft_free_arr(path);
		ft_exit_exec(sh->data, sh, 1);
	}
	return (full_path);
}

/**
 * @brief Wait for all child processes in pipeline and handle their exit status
 * @param shell Shell state containing command list with process IDs
 *
 * Process management:
 * - Iterates through all commands in the pipeline
 * - Waits for each child process to complete
 * - Analyzes exit status to determine how process terminated
 * - Sets global return value based on exit status or signal
 *
 * Exit status handling:
 * - Normal exit: Uses WEXITSTATUS() to get exit code
 * - Signal termination: Maps signals to conventional exit codes
 *   - SIGINT (Ctrl-C): 130
 *   - SIGQUIT (Ctrl-\): 131
 *
 * Signal propagation:
 * - If any process exits with 130 or 131, sets shell->stop = true
 * - This prevents further command execution in interactive mode
 *
 * Uses global g_exit_code to store the final exit status
 */

void	ft_waitpid(t_shell *shell)
{
	t_commands	*curr;
	int			status;

	curr = shell->cmds;
	while (curr)
	{
		if (curr->pid > 0)
		{
			waitpid(curr->pid, &status, 0);
			if (!curr->next && WIFEXITED(status))
				shell->data->exit_code = WEXITSTATUS(status);
			else if (!curr->next && WIFSIGNALED(status))
			{
				shell->data->exit_code = 128 + WTERMSIG(status);
				if (shell->data->exit_code == 130
					|| shell->data->exit_code == 131)
					shell->stop = true;
			}
		}
		curr = curr->next;
	}
}
/**
 * @brief Handle single built-in command execution without forking
 * @param shell Shell state containing the single command to execute
 * @return true if command was a built-in and executed, false otherwise
 *
 * Optimization for single built-in commands:
 * - Avoids unnecessary forking for built-ins when no pipeline exists
 * - Preserves original stdin/stdout for restoration after redirections
 * - Handles redirections properly for built-in commands
 *
 * Process:
 * 1. Check if the only command is a built-in
 * 2. Save current stdin/stdout file descriptors
 * 3. Apply any redirections (>, <, >>, <<)
 * 4. Execute the built-in command
 * 5. Restore original stdin/stdout
 *
 */

bool	single_cmd(t_shell *shell)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = -1;
	save_stdout = -1;
	if (is_builtin(shell->cmds))
	{
		if (set_fd_execution(shell, shell->cmds))
			return (true);
		save_stdin = ft_dup(STDIN_FILENO);
		save_stdout = ft_dup(STDOUT_FILENO);
		execute_builtin(shell->cmds, shell, save_stdin, save_stdout);
		ft_dup2(save_stdin, STDIN_FILENO);
		ft_dup2(save_stdout, STDOUT_FILENO);
		return (true);
	}
	return (false);
}
