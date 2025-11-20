/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:23:49 by haile         #+#    #+#                 */
/*   Updated: 2025/11/20 14:32:09 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

/**
 * @brief Execute a single command with PATH resolution
 * @param cmd Command structure containing command name and arguments
 * @param shell Shell state containing environment variables and PATH
 *
 * Execution priority:
 * 1. Check if command is empty (exit with status 0)
 * 2. Try built-in commands first
 * 3. Try current directory/absolute path execution
 * * 4. Search PATH environment variable for external commands.
 * Execute with PATH if found
 * 5. Fallback to execution without PATH if PATH not found
 *
 * This function always exits the process after execution attempt
 */
static void	execute_cmd(t_commands *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (!cmd->args)
	{
		ft_exit_exec(shell->data, shell, 0);
	}
	if (execute_builtin(cmd, shell, -1, -1))
		ft_exit_exec(shell->data, shell, shell->data->exit_code);
	if (execute_currdir(cmd, shell))
		ft_exit_exec(shell->data, shell, shell->data->exit_code);
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (shell->env[i])
	{
		ft_execve(cmd, shell, ft_split(&shell->env[i][5], ':'));
	}
	ft_execve(cmd, shell, NULL);
}

static void	setup_child_input(t_commands *cmd, int prev_fd)
{
	if (cmd->infile != -1)
	{
		if (prev_fd != -1)
			close(prev_fd);
		ft_dup2(cmd->infile, STDIN);
		close_existing_fd_in(cmd->infiles, &cmd->infile);
	}
	else if (prev_fd != -1)
	{
		ft_dup2(prev_fd, STDIN);
		close(prev_fd);
	}
}

static void	setup_child_output(t_commands *cmd)
{
	if (cmd->outfile != -1)
	{
		ft_dup2(cmd->outfile, STDOUT);
		close_existing_fd_out(cmd->outfiles, &cmd->outfile);
	}
	else if (cmd->next != NULL)
	{
		close(cmd->pipefd[0]);
		ft_dup2(cmd->pipefd[1], STDOUT);
		close(cmd->pipefd[0]);
	}
}

/**
 * @brief Handle pipe setup and process creation for pipeline commands
 * @param cmd Current command in the pipeline
 * @param prev_fd File descriptor from previous command's output (or
	-1 for first)
 * @param shell Shell state for environment and configuration
 *
 * Pipeline management:
 * - Sets up signal handling for pipeline execution
 * - Creates pipe if current command has a next command
 * - Forks child process for command execution
 * - In child: sets up input/output redirection via pipes
 * - Handles redirections before command execution
 * - Parent returns immediately to continue pipeline setup
 */
static void	handle_pipes(t_commands *cmd, int prev_fd, t_shell *shell)
{
	if (cmd->next != NULL)
		ft_pipe(cmd->pipefd);
	else
	{
		cmd->pipefd[0] = -1;
		cmd->pipefd[1] = -1;
	}
	cmd->pid = ft_fork();
	if (cmd->pid == 0)
	{
		setup_child_input(cmd, prev_fd);
		setup_child_output(cmd);
		execute_cmd(cmd, shell);
		exit(shell->data->exit_code);
	}
	else if (prev_fd != -1)
		close(prev_fd);
}

/**
 * @brief Main execution entry point - connects entire command pipeline
 * @param shell Shell state containing parsed commands and environment
 *
 * Execution flow:
 * 1. Process all heredocs first (<<)
 * 2. Check for single command optimization
 * 3. Create pipeline by iterating through linked command list
 * 4. For each command: setup pipes, fork process, manage file descriptors
 * 5. Wait for all child processes to complete
 *
 * Pipeline coordination:
 * - Maintains prev_fd to chain commands together
 * - closes file descriptors to avoid leaks
 * - Handles shell->stop flag for early termination
 */
void	execute(t_shell *shell)
{
	t_commands	*curr;
	int			prev_fd;

	curr = shell->cmds;
	while (curr)
		curr = curr->next;
	prev_fd = -1;
	curr = shell->cmds;
	if (curr->next == NULL && single_cmd(shell))
		return ;
	while (curr && !shell->stop)
	{
		if (!set_fd_execution(curr))
		{
			handle_pipes(curr, prev_fd, shell);
			if (prev_fd != -1)
				close(prev_fd);
			prev_fd = curr->pipefd[0];
			if (curr->pipefd[1] != -1)
				close(curr->pipefd[1]);
		}
		close_all_fd(curr);
		curr = curr->next;
	}
	ft_waitpid(shell);
}
