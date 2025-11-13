/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:23:49 by haile         #+#    #+#                 */
/*   Updated: 2025/11/11 13:41:41 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

//#include "libft.h"

/**git
 * @brief Execute command from current directory or with absolute/relative path
 * @param cmd Command structure containing command name and arguments
 * @param shell Shell state containing environment and configuration
 * @return true if command was executed successfully, false if not applicable
 *
 * This function handles:
 * - Empty command validation (exits with 127)
 * - Commands with '/' (absolute/relative paths)
 * - File accessibility checks before execution
 * - Direct execve() calls for path-based commands
 */
static bool	execute_currdir(t_commands *cmd, t_shell *shell)
{
	if (cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: : command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (ft_strchr(cmd->args[0], '/') == NULL)
		return (false);
	if (access(cmd->args[0], F_OK) == 0)
	{
		if (execve(cmd->args[0], cmd->args, shell->env) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(cmd->args[0]);
			exit(126);
		}
	}
	return (false);
}

/**
 * @brief Execute built-in shell commands
 * @param cmd Command structure containing command name and arguments
 * @param shell Shell state for environment and configuration access
 * @return 1 if command was a built-in and executed, 0 if not a built-in
 *
 * Supported built-ins:
 * - pwd: Print working directory
 * - echo: Display text with optional -n flag
 * - cd: Change directory
 * - export: Set environment variables
 * - unset: Remove environment variables
 * - env: Display environment variables
 * - exit: Exit the shell
 *
 * Uses global g_exit_code to store the exit status of executed built-ins
 */
int	execute_builtin(t_commands *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		g_exit_code = ft_pwd();
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		g_exit_code = ft_echo(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		g_exit_code = ft_cd(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		g_exit_code = ft_export(cmd, shell, 0);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		g_exit_code = ft_unset(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		g_exit_code = ft_env(shell->env);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		g_exit_code = ft_exit(cmd);
	else
		return (0);
	return (1);
}

/**
 * @brief Execute a single command with PATH resolution
 * @param cmd Command structure containing command name and arguments
 * @param shell Shell state containing environment variables and PATH
 *
 * Execution priority:
 * 1. Check if command is empty (exit with status 0)
 * 2. Try built-in commands first
 * 3. Try current directory/absolute path execution

	* 4. Search PATH environment variable for external commands.
	Execute with PATH if found
 * 5. Fallback to execution without PATH if PATH not found
 *
 * This function always exits the process after execution attempt
 */
static void	execute_cmd(t_commands *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (!cmd->args[0])
		exit(0);
	// printf("EXECUTING: %s\n", cmd->args[0]);
	if (execute_builtin(cmd, shell))
	{
		// printf("Built-in executed\n");
		exit(g_exit_code);
	}
	// printf("Not a builtin, trying external command: %s\n", cmd->args[0]);
	if (execute_currdir(cmd, shell))
	{
		// printf("Current dir executed\n");
		exit(g_exit_code);
	}
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (shell->env[i])
	{
		// printf("Searching PATH...\n");
		ft_execve(cmd, shell, ft_split(&shell->env[i][5], ':'));
	}
	// printf("No PATH, trying direct execution\n");
	ft_execve(cmd, shell, NULL);
	// Try built-in first, then current directory execution
	// 	if (!execute_builtin(cmd, shell) && !execute_currdir(cmd, shell))
	// 	{
	// 		// Search for PATH environment variable
	// 		while (shell->env && shell->env[i])
	// 		{
	// 			if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
	// 				break ;
	// 			i++;
	// 		}
	// 		// Execute with PATH if found, otherwise try without PATH
	// 		if (shell->env[i])
	// 			ft_execve(cmd, shell, ft_split(&shell->env[i][5], ':'));
	// 		ft_execve(cmd, shell, NULL);
	// 	}
	// 	exit(g_exit_code);
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
	// sig_handler(1); //Command out for now Max because of missing function
	// printf("🔧 HANDLE_PIPES called for: %s\n", cmd->args[0]);//debug
	if (cmd->next != NULL)
	{
		ft_pipe(cmd->pipefd);
		// printf("Created pipe: read=%d, write=%d\n", cmd->pipefd[0],
			cmd->pipefd[1]);
	}
	else
	{
		cmd->pipefd[0] = -1;
		cmd->pipefd[1] = -1;
		// printf("No pipe needed (last command)\n");
	}
	// printf("About to fork for command: %s (n=%d)\n", cmd->args[0], cmd->n);
	// debug
	cmd->pid = ft_fork();
	if (cmd->pid == 0)
	{
		if (set_fd_execution(cmd))
			printf("should not reach here\n");
		// printf("CHILD PROCESS for: %s (pid=%d)\n", cmd->args[0], getpid());
		// sig_handler(2); //Command out for now Max because of missing function
		// new add 04/11 - Setup input redirection from previous command
		// if (cmd->n > 1) //Command out for now
		if (cmd->infile != -1)
		{
			// printf("Child: Redirecting stdin to fd %d\n", cmd->infile);
			ft_dup2(cmd->infile, STDIN);
			close_existing_fd_out(find_open_fd(cmd->infiles), &cmd->infile);
		}
		else if (prev_fd != -1)
		{
			// printf("Child: Redirecting stdin from fd %d\n", prev_fd);
			ft_dup2(prev_fd, STDIN);
			close(prev_fd); // new add 04/11 - Close after dup2
		}
		else
			printf("Child: No input redirection needed\n");
		if (cmd->outfile != -1)
		{
			// printf("Child: Redirecting stdout to fd %d\n", cmd->outfile);
			ft_dup2(cmd->outfile, STDOUT);
			close_existing_fd_in(find_open_fd(cmd->outfiles), &cmd->outfile);
		}
		else if (cmd->next != NULL)
		{
			// printf("Child: Redirecting stdout to fd %d\n", cmd->pipefd[1]);
			close(cmd->pipefd[0]); // new add 04/11
									//- Close read end (don't need it)
			ft_dup2(cmd->pipefd[1], STDOUT);
			close(cmd->pipefd[0]); // new add 04/11 - Close after dup2
		}
		else
			printf("Child: No output redirection needed\n");
		// printf("Child: About to execute: %s\n", cmd->args[0]);
		// Command out for now Max because of missing function
		execute_cmd(cmd, shell);
		exit(g_exit_code);
	}
	else // debug part. Need to check
	{
		// Parent process - clean up file descriptors
		// printf("PARENT: Child pid=%d for command: %s\n", cmd->pid,
			cmd->args[0]);
		if (prev_fd != -1)
		{
			// printf("Parent: Closing prev_fd %d\n", prev_fd);
			close(prev_fd); // Close the read end we passed to child
		}
		// if (cmd->pipefd[1] != -1)
		//     close(cmd->pipefd[1]);  // Close write end - child owns it now
	}
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
 * - Properly closes file descriptors to avoid leaks
 * - Handles shell->stop flag for early termination
 */
void	execute(t_shell *shell)
{
	t_commands	*curr;
	int			prev_fd;
	int			cmd_count;

	// printf("=== EXECUTE START ===\n");
	// Process heredocs before any command execution
	// handle_heredocs(shell);
	// printf("COMMAND LIST DEBUG:\n");
	curr = shell->cmds;
	cmd_count = 0;
	while (curr)
	{
		// printf("Command %d: %s (next=%p)\n", cmd_count, curr->args[0],
			(void *)curr->next);
		curr = curr->next;
		cmd_count++;
	}
	// printf("Total commands: %d\n", cmd_count);
	prev_fd = -1;
	curr = shell->cmds;
	// Optimization: handle single command without unnecessary forking
	if (curr->next == NULL && single_cmd(shell))
	{
		// printf("Single command executed\n");
		return ;
	}
	// printf("start main execution loop\n");
	// Execute pipeline: iterate through all commands
	while (curr && !shell->stop)
	{
		// printf("Processing command: %s (pid will be %d)\n", curr->args[0],
		// 	curr->pid);
		handle_pipes(curr, prev_fd, shell);
		// printf("handle_pipes completed for %s (pid=%d)\n", curr->args[0],
			curr->pid);
		// Clean up file descriptors
		if (prev_fd != -1)
		{
			// printf("Closing prev_fd: %d\n", prev_fd);
			close(prev_fd);
			// Close previous read end
		}
		prev_fd = curr->pipefd[0]; // Save current read end for next command
		if (curr->pipefd[1] != -1)
		{
			// printf("Closing write end: %d\n", curr->pipefd[1]);
			close(curr->pipefd[1]);
			// Close current write end
		}
		curr = curr->next; // Move to next command
	}
	// printf("======================\n");
	ft_waitpid(shell);
	// Wait for all child processes to complete
	// printf("=== EXECUTE END ===\n");
}
