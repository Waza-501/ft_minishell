/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_bridge.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/14 11:55:10 by haile         #+#    #+#                 */
/*   Updated: 2025/11/17 12:41:56 by haile         ########   odam.nl         */
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
 * @brief Clean up execution-specific fields in
 * commands after execution
 * @param cmd_list Command list to clean up
 * Flow: Close any open pipe file descriptors
 * --> After close then reset process ID
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
	t_shell	shell;

	if (init_shell_for_execution(&shell, data) != 0)
		return (1);
	if (init_commands_for_execution(data->commands) != 0)
		return (cleanup_shell(&shell), 1);
	shell.cmds = data->commands;
	execute(&shell);
	cleanup_shell(&shell);
	return (0);
}

static char	*create_env_string(t_cd_ll_node *node)
{
	char	*temp_key_eq;
	char	*full_var;

	temp_key_eq = ft_strjoin(node->var_1, "=");
	if (!temp_key_eq)
		return (NULL);
	full_var = ft_strjoin(temp_key_eq, node->var_2);
	free(temp_key_eq);
	return (full_var);
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

	i = 0;
	if (!env_list || !env_list->head)
		return (NULL);
	env_array = malloc(sizeof(char *) * (env_list->size + 1));
	if (!env_array)
		return (NULL);
	current = env_list->head;
	while (current && i < env_list->size)
	{
		env_array[i] = create_env_string(current);
		if (!env_array[i])
			return (NULL);
		current = current->next;
		i++;
		if (current == env_list->head)
			break ;
	}
	env_array[i] = NULL;
	return (env_array);
}
