/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_bridge.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/14 11:55:10 by haile         #+#    #+#                 */
/*   Updated: 2025/11/14 11:53:00 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief int init_commands_for_execution(t_commands *cmd_list)
 * @param cmd_list Parser's t_commands linked list
 * @return 0 on success, 1 on failure
 */
int	init_commands_for_execution(t_commands *cmd_list)
{
	t_commands	*current;
	int			cmd_number;

	current = cmd_list;
	cmd_number = 0;
	while (current)
	{
		// printf("🔧 INIT_COMMANDS_FOR_EXECUTION CALLED!\n");
		// Initialize execution fields that parser doesn't set
		current->pid = -1;       // No process yet
		current->pipefd[0] = -1; // No pipe yet
		current->pipefd[1] = -1;
		current->n = cmd_number; // Set command number
		// current->heredoc = NULL;        // Will be set by heredoc handler
		// printf("🔧 Setting command %p to number %d\n", current, cmd_number);
		current = current->next;
		cmd_number++;
	}
	return (0);
}
/**
 * @brief Clean up execution-specific fields in commands after execution
 * @param cmd_list Command list to clean up
 */
void	cleanup_execution_fields(t_commands *cmd_list)
{
	t_commands	*current;

	current = cmd_list;
	while (current)
	{
		// Close any open pipe file descriptors
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
		// Reset process ID
		current->pid = -1;
		current = current->next;
	}
}
/**
 * @brief Main execution entry point - connects parser output to executor
 * @param data Main data structure containing parsed commands and environment
 * @return Execution status (0 = success, non-zero = error)
 */
// int execute_commands(t_data *data)
// {
//     t_shell shell;

//     if (init_shell_for_execution(&shell, data) != 0)
// Initialize shell structure for executor
//         return (1);
//     if (init_commands_for_execution(data->commands) != 0)
// Initialize execution fields in the command list
//         return (cleanup_shell(&shell), 1);
//     shell.cmds = data->commands;
//     // Execute the command pipeline
//     execute(&shell);
//     data->exit_code = g_exit_code;
//     // Cleanup
//     cleanup_shell(&shell);
//     return (0);
// }
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
	// printf("  Total shell commands: %d\n", debug_count);
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
 */
int	init_shell_for_execution(t_shell *shell, t_data *data)
{
	if (!shell || !data)
		return (1);
	// Convert environment from circular linked list to array
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
	// Allocate array
	env_array = malloc(sizeof(char *) * (env_list->size + 1));
	if (!env_array)
		return (NULL);
	// Convert each node to "KEY=VALUE" format
	current = env_list->head;
	while (current && i < env_list->size)
	{
		// Step 1: Create "KEY=" string
		temp_key_eq = ft_strjoin(current->var_1, "=");
		if (!temp_key_eq)
		{
			// Cleanup on failure
			while (--i >= 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		// Step 2: Create "KEY=VALUE" string
		full_var = ft_strjoin(temp_key_eq, current->var_2);
		free(temp_key_eq);
		if (!full_var)
		{
			// Cleanup on failure
			while (--i >= 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		env_array[i] = full_var;
		// env_array[i] = ft_strjoin(current->var_1, "=");
		// if (!env_array[i])
		//     return (ft_free_arr(env_array), NULL);
		// char *temp = env_array[i];
		// env_array[i] = ft_strjoin(temp, current->var_2);
		// free(temp);
		// if (!env_array[i])
		//     return (ft_free_arr(env_array), NULL);
		current = current->next;
		i++;
		// Break if we've completed the circular list
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
