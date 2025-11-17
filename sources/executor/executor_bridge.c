/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_bridge.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/14 11:55:10 by haile         #+#    #+#                 */
/*   Updated: 2025/11/17 09:41:18 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief int init_commands_for_execution(t_commands *cmd_list)
 * @param cmd_list Parser's t_commands linked list
 * @return 0 on success, 1 on failure
 * Flow: Initialize execution fields that parser doesn't set
 *
 */
int	init_commands_for_execution(t_commands *cmd_list)
{
	t_commands	*current;
	int			cmd_number;

	current = cmd_list;
	cmd_number = 0;
	while (current)
	{
		current->pid = -1;
		current->pipefd[0] = -1;
		current->pipefd[1] = -1;
		current->n = cmd_number;
		current = current->next;
		cmd_number++;
	}
	return (0);
}
/**
 * @brief Clean up execution-specific fields in commands after execution
 * @param cmd_list Command list to clean up

	* Flow: Close any open pipe file descriptors --> After close then reset process ID
 */
void	cleanup_execution_fields(t_commands *cmd_list)
{
	t_commands	*current;

	current = cmd_list;
	while (current)
	{
		if (current->pipefd[0] > 2)
		{
			close(current->pipefd[0]);
			current->pipefd[0] = -1;
		}
		if (current->pipefd[1] > 2)
		{
			close(current->pipefd[1]);
			current->pipefd[1] = -1;
		}
		current->pid = -1;
		current = current->next;
	}
}
/**
 * @brief Main execution entry point - connects parser output to executor
 * @param data Main data structure containing parsed commands and environment
 * @return Execution status (0 = success, non-zero = error)
 */
int	execute_commands(t_data *data)
{
	t_shell		shell;
	t_commands	*debug_curr;
	int			debug_count;

	// CRITICAL DEBUG: Check data->commands BEFORE assignment
	// printf("🔍 DATA->COMMANDS DEBUG (before assignment):\n");
	debug_curr = data->commands;
	debug_count = 0;
	while (debug_curr)
	{
		// printf("  Data Command %d: %s (next=%p)\n", debug_count,
		// 	debug_curr->args[0] ? debug_curr->args[0] : "NULL",
		// 	(void *)debug_curr->next);
		debug_curr = debug_curr->next;
		debug_count++;
		if (debug_count > 10) // Safety check
			break ;
	}
	// printf("  Total data commands: %d\n", debug_count);
	// printf("  data->commands pointer: %p\n", (void *)data->commands);
	if (init_shell_for_execution(&shell, data) != 0)
		return (1);
	if (init_commands_for_execution(data->commands) != 0)
		return (cleanup_shell(&shell), 1);
	shell.cmds = data->commands;
	// CRITICAL DEBUG: Check shell.cmds AFTER assignment
	// printf(" SHELL->CMDS DEBUG (after assignment):\n");
	debug_curr = shell.cmds;
	debug_count = 0;
	while (debug_curr)
	{
		// printf("  Shell Command %d: %s (next=%p)\n", debug_count,
		// 	debug_curr->args[0] ? debug_curr->args[0] : "NULL",
		// 	(void *)debug_curr->next);
		debug_curr = debug_curr->next;
		debug_count++;
		if (debug_count > 10) // Safety check
			break ;
	}
	printf("  Total shell commands: %d\n", debug_count);
	// printf("  shell.cmds pointer: %p\n", (void *)shell.cmds);
	// Execute the command pipeline
	execute(&shell);
	// Cleanup
	cleanup_shell(&shell);
	return (0);
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
 * @brief Convert circular doubly linked list environment to char** array
 * Flow: Allocate array -> Convert each node to "KEY=VALUE" format (while loop)
 * temp_key_eq: Create "KEY=" string, noted to clean up on failure
 * full_var: Step 2: Create "KEY=VALUE" string
 * Break if we've completed the circular list
 */
char	**convert_cdll_to_env_array(t_cdllist *env_list)
{
	char			**env_array;
	t_cd_ll_node	*current;
	int				i;
	char			*temp_key_eq;
	char			*full_var;

	i = 0;
	if (!env_list || !env_list->head)
		return (NULL);
	env_array = malloc(sizeof(char *) * (env_list->size + 1));
	if (!env_array)
		return (NULL);
	current = env_list->head;
	while (current && i < env_list->size)
	{
		temp_key_eq = ft_strjoin(current->var_1, "=");
		if (!temp_key_eq)
		{
			while (--i >= 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		full_var = ft_strjoin(temp_key_eq, current->var_2);
		free(temp_key_eq);
		if (!full_var)
		{
			while (--i >= 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		env_array[i] = full_var;
		current = current->next;
		i++;
		if (current == env_list->head)
			break ;
	}
	env_array[i] = NULL;
	return (env_array);
}

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
