/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils3.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/17 12:40:27 by haile         #+#    #+#                 */
/*   Updated: 2025/11/26 13:18:09 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sync changes back to linked list BEFORE freeing
 * Free environment array (created by convert_cdll_to_env_array)
 * Clean up other fields
 */
void	cleanup_shell(t_shell *shell)
{
	int	i;

	if (!shell)
		return ;
	if (shell->env && shell->data && shell->data->envp_copy)
		sync_env_to_list(shell->env, shell->data->envp_copy);
	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
		shell->env = NULL;
	}
	shell->cmds = NULL;
	shell->data = NULL;
	shell->stop = false;
}

/**
 * @brief Initialize shell structure from data structure
 * @param shell Shell structure to initialize
 * @param data Main data structure containing environment and commands
 * @return 0 on success, 1 on failure
 * Flow: Convert environment from circular linked list to array
 */
int	init_shell_for_execution(t_shell *shell, t_data *data)
{
	if (!shell || !data)
		return (1);
	shell->env = convert_cdll_to_env_array(data->envp_copy);
	if (!shell->env)
		return (1);
	shell->cmds = NULL;
	shell->stop = false;
	shell->data = data;
	return (0);
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
 * Uses to store the exit status of executed built-ins
 */
int	execute_builtin(t_commands *cmd, t_shell *shell, int fd_0, int fd_1)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		shell->data->exit_code = ft_pwd();
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		shell->data->exit_code = ft_echo(cmd);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		shell->data->exit_code = ft_cd(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		shell->data->exit_code = ft_export(cmd, shell, 0);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		shell->data->exit_code = ft_unset(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		shell->data->exit_code = ft_env(shell->env);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		shell->data->exit_code = ft_exit(shell, cmd, fd_0, fd_1);
	else
		return (0);
	return (1);
}

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
bool	execute_currdir(t_commands *cmd, t_shell *shell)
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
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->args[0]);
		exit(127);
	}
	return (false);
}

/**
 * @brief Execute external command by searching through PATH directories
 * @param cmd Command structure containing command name and arguments
 * @param shell Shell state for environment access
 * @param path Array of PATH directories to search (can be NULL)
 *
 * Execution process:
 * 1. If path is provided, search each directory for the command
 * 2. Construct full path by joining directory + "/" + command_name
 * 3. Check if constructed path exists and is accessible
 * 4. Attempt execution with execve()
 * 5. If command not found in any PATH directory, exit with 127
 *
 * Memory management:
 * - Frees path array before exit
 * - Frees temporary path strings during search
 *
 * Exit codes:
 * - 127: Command not found
 * - -1: execve() failed but file was found (shouldn't happen normally)
 *
 * This function always exits the process - never returns to caller.
 */

void	ft_execve(t_commands *cmd, t_shell *shell, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!path)
	{
		tmp = ft_strdup(cmd->args[0]);
		if (!tmp)
			ft_exit_exec(shell->data, shell, 1);
		try_execute_path(tmp, cmd, shell, path);
		free(tmp);
	}
	while (path && path[i])
	{
		tmp = build_full_path(path[i], cmd->args[0], path, shell);
		try_execute_path(tmp, cmd, shell, path);
		free(tmp);
		i++;
	}
	ft_free_arr(path);
	print_error(cmd->args[0]);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	ft_exit_exec(shell->data, shell, 127);
}
