/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 12:27:15 by haile         #+#    #+#                 */
/*   Updated: 2025/11/11 13:22:09 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

/**
 * @brief Execute commands using shell (replaces execute_commands)
 * This function now correctly routes commands:
 * - Pipeline commands (cmd->next exists) → original executor with pipe handling
 * - Single commands → persistent shell execution for builtins like export/cd
 *
 *
 * */
void	execute_with_shell(t_shell *shell, t_data *data)
{
	if (!data || !shell || !data->commands)
		return ;
	// CRITICAL FIX: Detect pipelines and route appropriately
	if (data->commands && data->commands->next)
	{
		// printf("Pipeline detected: routing to original executor\n");
		// Pipeline detected: use original executor with proper pipe handling
		shell->cmds = data->commands; // Set full pipeline
		execute(shell);               // Use original pipeline executor
		return ;
	}
	// printf("Single command: using persistent shell execution\n");
	// Single command: use persistent shell execution for builtins
	execute_single_command(data->commands, shell, data);
}

/**
 * @brief Execute a single command with shell
 * Check if it's a builtin that benefits from shell persistence
 * CD might change PWD, invalidate sorted env cache
 */
void	execute_single_command(t_commands *cmd, t_shell *shell, t_data *data)
{
	int	i;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (set_fd_execution(cmd))
		return ;
	if (ft_strncmp(cmd->args[0], "export", 6) == 0)
	{
		// printf("Executing builtin: export\n");
		shell_export(shell, cmd->args);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
		// printf("Executing builtin: unset\n");
		i = -1;
		while (cmd->args[++i])
			shell_unset(shell, cmd->args[i]);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "env", 3) == 0)
	{
		// printf("Executing builtin: env\n");
		ft_env(shell->env);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
	{
		// printf("Executing builtin: cd\n");
		ft_cd(cmd, shell);
		invalidate_sorted_env(shell);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
	{
		// printf("Executing builtin: pwd\n");
		ft_pwd();
		return ;
	}
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
	{
		// printf("Executing builtin: echo\n");
		ft_echo(cmd);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
	{
		// printf("Executing builtin: exit\n");
		ft_exit(cmd);
		return ;
	}
	// printf("Executing external command: %s\n", cmd->args[0]);
	execute_other_commands(cmd, shell, data);
}

/**
 * @brief Execute non-builtin commands using existing system
 * Create temporary shell structure for compatibility with existing executor.
 * This allows external commands to work with the existing pipeline infrastructure
 * while preserving important shell state after execution.
 */
void	execute_other_commands(t_commands *cmd, t_shell *shell, t_data *data)
{
	t_shell	temp_shell = {0};

	(void)data;
	temp_shell.env = shell->env;
	temp_shell.cmds = cmd;
	temp_shell.stop = shell->stop;
	temp_shell.data = shell->data;
	temp_shell.sorted_env = shell->sorted_env;
	temp_shell.sorted_env_valid = shell->sorted_env_valid;
	execute(&temp_shell);
	shell->stop = temp_shell.stop;
	shell->sorted_env_valid = temp_shell.sorted_env_valid;
}

/**
 * @brief Quick argument parser for simple commands
 * Used for parsing simple command strings when needed
 */
char	**quick_parse_args(char *input)
{
	char	**args;
	char	*input_copy;
	char	**tokens;
	int		i;

	args = ft_calloc(10, sizeof(char *));
	if (!args)
		return (NULL);
	input_copy = ft_strdup(input);
	tokens = ft_split(input_copy, ' ');
	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens && i < 9)
	{
		args[i] = tokens[i];
		i++;
	}
	args[i] = NULL;
	free(input_copy);
	return (args);
}

/**
 * @brief Free quick args memory
 */
void	free_quick_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}
