/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: your_name                                     +#+                     */
/*                                                   +#+                      */
/*   Created: Shell execution with persistence                                */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute commands using shell (replaces execute_commands)
 * Works with your existing parse_input system
 */
void execute_with_shell(t_shell *shell, t_data *data)
{   
    t_commands *cmd;
    if (!data || !shell || !data->commands)
        return;
    
    cmd = data->commands;
    
    // Process each command in the pipeline
    while (cmd)
    {
        execute_single_command(cmd, shell, data);
        cmd = cmd->next;
    }
}

/**
 * @brief Execute a single command with shell persistence
 */
void execute_single_command(t_commands *cmd, t_shell *shell, t_data *data)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return;
    // Check if it's a builtin that benefits from shell persistence
    if (ft_strncmp(cmd->args[0], "export", 6) == 0)
    {
        shell_export(shell, cmd->args);
        return;
    }
    if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
    {
        for (int i = 1; cmd->args[i]; i++)
        {
            shell_unset(shell, cmd->args[i]);
        }
        return;
    }
    if (ft_strncmp(cmd->args[0], "env", 3) == 0)
    {
        ft_env(shell->env);
        return;
    }
    // if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
    // {
    //     ft_cd(cmd, shell);
    //     // CD might change PWD, invalidate sorted env cache
    //     invalidate_sorted_env(shell);
    //     return;
    // }
    if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
    {
        ft_pwd();
        return;
    }
    if (ft_strncmp(cmd->args[0], "echo", 4) == 0)
    {
        ft_echo(cmd);
        return;
    }
    // if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
    // {
    //     ft_exit(cmd);
    //     return;
    // }
    // For other commands, use your existing execution system
    execute_other_commands(cmd, shell, data);
}

/**
 * @brief Execute non-builtin commands using existing system
 * You can hook into your existing executor here
 */
void execute_other_commands(t_commands *cmd, t_shell *shell, t_data *data)
{
    // Create temporary shell structure for compatibility with existing executor
    t_shell temp_shell = {0};
    temp_shell.env = shell->env;  // Use persistent environment
    temp_shell.cmds = cmd;
    temp_shell.stop = shell->stop;
    temp_shell.data = shell->data;
    temp_shell.sorted_env = shell->sorted_env;           // Copy cache
    temp_shell.sorted_env_valid = shell->sorted_env_valid; // Copy validity
    // Call your existing execute function
    // You can replace this with your actual executor function
    execute(&temp_shell);  // Your existing execute function
    
    // Copy back any important state
    shell->stop = temp_shell.stop;
    shell->sorted_env_valid = temp_shell.sorted_env_valid; // Update validity
}

/**
 * @brief Quick argument parser for simple commands
 */
char **quick_parse_args(char *input)
{
    char **args = ft_calloc(10, sizeof(char*));
    if (!args)
        return (NULL);
    char *input_copy = ft_strdup(input);
    char **tokens = ft_split(input_copy, ' ');
    if (!tokens)
        return (NULL);
    int i = 0;
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
void free_quick_args(char **args)
{
    if (!args)
        return;
        
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}
