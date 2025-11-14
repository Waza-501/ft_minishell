/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_executor copy.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 12:27:15 by haile         #+#    #+#                 */
/*   Updated: 2025/11/14 11:23:12 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute commands using shell (replaces execute_commands)
 * Works with your existing parse_input system
 */
// void execute_with_shell(t_shell *shell, t_data *data)
// {
//     t_commands *cmd;
//     if (!data || !shell || !data->commands)
//         return ;

//     cmd = data->commands;

//     // Process each command in the pipeline
//     while (cmd)
//     {
//         execute_single_command(cmd, shell, data);
//         cmd = cmd->next;
//     }
// }
void	execute_with_shell(t_shell *shell, t_data *data)
{
	t_commands	*cmd;
	t_commands	*debug_curr;
	int			debug_count;

	if (!data || !shell || !data->commands)
		return ;
	//Check data->commands at entry
	// printf("DATA->COMMANDS DEBUG (execute_with_shell entry):\n");
	debug_curr = data->commands;
	debug_count = 0;
	while (debug_curr)
	{
		// printf("Data Command %d: %s (next=%p)\n", debug_count,
		// 	debug_curr->args[0] ? debug_curr->args[0] : "NULL",
		// 	(void *)debug_curr->next);
		debug_curr = debug_curr->next;
		debug_count++;
		if (debug_count > 10)
			break ;
	}
	// printf("Total data commands: %d\n", debug_count);
	// printf("data->commands pointer: %p\n", (void *)data->commands);
	cmd = data->commands;
	// Process each command in the pipeline
	while (cmd)
	{
		// printf("execute_with_shell processing: %s (next=%p)\n",
		// 	cmd->args[0] ? cmd->args[0] : "NULL", (void *)cmd->next);
		execute_single_command(cmd, shell, data);
		cmd = cmd->next;
	}
}

/**
 * @brief Execute a single command with shell
 * Check if it's a builtin that benefits from shell persistence
 * CD might change PWD, invalidate sorted env cache
 */
void	execute_single_command(t_commands *cmd, t_shell *shell, t_data *data)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (ft_strncmp(cmd->args[0], "export", 6) == 0)
	{
		shell_export(shell, cmd->args);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
		for (int i = 1; cmd->args[i]; i++)
		{
			shell_unset(shell, cmd->args[i]);
		}
		return ;
	}
	if (ft_strncmp(cmd->args[0], "env", 3) == 0)
	{
		ft_env(shell->env);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
	{
		ft_cd(cmd, shell);
		invalidate_sorted_env(shell);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
	{
		ft_pwd();
		return ;
	}
	if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
	{
		ft_echo(cmd);
		return ;
	}
	if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
	{
		ft_exit(cmd);
		return ;
	}
	execute_other_commands(cmd, shell, data);
}

/**
 * @brief Execute non-builtin commands using existing system
 * You can hook into your existing executor here
 *
	* Create temporary shell structure for compatibility with existing executor.
	Copy cache
 * After execution copy back important state and update validity
 */
void	execute_other_commands(t_commands *cmd, t_shell *shell, t_data *data)
{
    (void)data;
	t_shell	temp_shell = {0};

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
 * @brief Free quick args
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
