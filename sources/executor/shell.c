/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: your_name                                     +#+                     */
/*                                                   +#+                      */
/*   Created: Clean shell implementation                                      */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize shell with full environment ownership
 * REPLACES any existing init_shell function
 */
t_shell *init_shell(t_data *data)
{
    t_shell *shell;
    
    shell = ft_malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);
    // Take full ownership of environment by converting from circular list
    shell->env = convert_cdll_to_env_array(data->envp_copy);
    if (!shell->env)
    {
        free(shell);
        return (NULL);
    }
    // Initialize shell state
    shell->cmds = NULL;
    shell->stop = false;
    shell->sorted_env = NULL;
    shell->sorted_env_valid = false;  // No sorted_env cached yet
    shell->data = data;
    return (shell);
}

/**
 * @brief Clean up shell (called at program exit)
 * REPLACES any existing cleanup_shell function
 */
void cleanup_shell(t_shell *shell)
{
    if (!shell)
        return;
    // Free environment array (we own it completely)
    if (shell->env)
        ft_free_arr(shell->env);
    // Free cached sorted environment
    if (shell->sorted_env)
        ft_free_arr(shell->sorted_env);
    free(shell);
}

/**
 * @brief Mark sorted environment as invalid (needs regeneration)
 */
void invalidate_sorted_env(t_shell *shell)
{
    if (!shell)
        return;
    shell->sorted_env_valid = false;
}

/**
 * @brief Get sorted environment (lazy generation)
 */
char **get_sorted_env(t_shell *shell)
{
    if (!shell)
        return (NULL);
    // If sorted_env is valid, return cached version
    if (shell->sorted_env_valid && shell->sorted_env)
        return (shell->sorted_env);
    // Need to regenerate sorted_env
    if (shell->sorted_env)
        ft_free_arr(shell->sorted_env);
    // Use existing sort_env function
    shell->sorted_env = sort_env(shell->env);
    shell->sorted_env_valid = true;
    return (shell->sorted_env);
}

/**
 * @brief Export function for shell
 * REPLACES your existing ft_export
 */
int shell_export(t_shell *shell, char **args)
{
    if (!shell)
        return (1);
    // No arguments - display sorted environment
    if (!args[1])
    {
        char **sorted = get_sorted_env(shell);
        if (!sorted)
        {
            g_exit_code = 1;
            return (1);
        }
        // Use existing print_env function
        print_env(sorted);
        return (0);
    }
    // Has arguments - add/update variables
    char *str = args[1];
    // Use existing if_exist function
    if (!if_exist(shell->env, str))
    {
        // Variable doesn't exist, need to add it
        int count = 0;
        while (shell->env[count])
            count++;
        char **new_env = ft_malloc((count + 2) * sizeof(char*));
        if (!new_env)
        {
            g_exit_code = 1;
            return (1);
        }
        // Copy existing variables
        for (int i = 0; i < count; i++)
            new_env[i] = ft_strdup(shell->env[i]);
        // Add new variable
        new_env[count] = ft_strdup(str);
        new_env[count + 1] = NULL;
        // Replace old environment
        ft_free_arr(shell->env);
        shell->env = new_env;
    }
    // Invalidate sorted cache
    invalidate_sorted_env(shell);
    g_exit_code = 0;
    return (0);
}

/**
 * @brief Unset environment variable in shell
 */
int shell_unset(t_shell *shell, char *name)
{
    if (!shell || !name)
        return (1);
    int count = 0;
    int found = -1;
    int name_len = ft_strlen(name);
    
    // Count variables and find target
    while (shell->env[count])
    {
        if (ft_strncmp(shell->env[count], name, name_len) == 0 &&
            shell->env[count][name_len] == '=')
        {
            found = count;
        }
        count++;
    }
    // If not found, nothing to do
    if (found == -1)
        return (0);
    // Create new array without the target variable
    char **new_env = ft_malloc(count * sizeof(char*));
    if (!new_env)
        return (1);
    int j = 0;
    for (int i = 0; i < count; i++)
    {
        if (i != found)
        {
            new_env[j] = ft_strdup(shell->env[i]);
            j++;
        }
    }
    new_env[j] = NULL;
    // Replace environment
    ft_free_arr(shell->env);
    shell->env = new_env;
    invalidate_sorted_env(shell);
    return (0);
}

/**
 * @brief Set environment variable in shell
 */
int shell_setenv(t_shell *shell, char *name, char *value)
{
    if (!shell || !name || !value)
        return (1);
    // Create name=value string
    char *temp = ft_strjoin(name, "=");
    if (!temp)
        return (1);
    char *env_str = ft_strjoin(temp, value); 
    if (!env_str)
        return (1);
    free(temp);
    // Use existing if_exist to update or add
    if (!if_exist(shell->env, env_str))
    {
        // Need to add new variable
        int count = 0;
        while (shell->env[count])
            count++;
        char **new_env = ft_malloc((count + 2) * sizeof(char*));
        if (!new_env)
        {
            free(env_str);
            return (1);
        }
        for (int i = 0; i < count; i++)
            new_env[i] = ft_strdup(shell->env[i]);
        new_env[count] = ft_strdup(env_str);
        new_env[count + 1] = NULL;
        ft_free_arr(shell->env);
        shell->env = new_env;
    }
    free(env_str);
    invalidate_sorted_env(shell);
    return (0);
}
