/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:23:18 by haile         #+#    #+#                 */
/*   Updated: 2025/11/04 12:40:45 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Update PWD and OLDPWD environment variables
 * @param shell Shell structure
 * @param old_pwd The previous working directory
 * @return 0 on success, -1 on failure
 */
int update_pwd_vars(t_shell *shell, char *old_pwd)
{
    char *new_pwd;
    int i = 0;
    int pwd_updated = 0;
    int oldpwd_updated = 0;

    new_pwd = get_pwd();
    if (!new_pwd)
        return (-1);

    // Update existing PWD and OLDPWD entries
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
        {
            free(shell->env[i]);
            shell->env[i] = ft_strjoin("PWD=", new_pwd);
            if (!shell->env[i])
            {
                free(new_pwd);
                return (-1);
            }
            pwd_updated = 1;
        }
        else if (ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0)
        {
            free(shell->env[i]);
            shell->env[i] = ft_strjoin("OLDPWD=", old_pwd);
            if (!shell->env[i])
            {
                free(new_pwd);
                return (-1);
            }
            oldpwd_updated = 1;
        }
        i++;
    }

    free(new_pwd);
    
    // TODO: If PWD or OLDPWD don't exist, we should add them to the environment
    // This would require expanding the env array, which needs modify_path function
    if (!pwd_updated || !oldpwd_updated)
    {
        // For now, we'll just warn about missing variables
        // In a complete implementation, we'd call modify_path here
        printf("Warning: PWD or OLDPWD variable missing in environment\n");
    }
    
    return (0);
}
/**
 * @brief Extract environment variable value
 * @param path Environment variable name with = (e.g., "HOME=")
 * @param shell Shell structure with environment
 * @return Allocated string with variable value or NULL if not found
 */
char    *extract_path(char *path, t_shell *shell)
{
    int i;
    int path_len;

    i = 0;
    path_len = ft_strlen(path);
    while (shell->env[i])
    {
        if (!ft_strncmp(shell->env[i], path, path_len))
            return (ft_substr(shell->env[i], path_len, ft_strlen(shell->env[i]) - path_len));
        i++;
    }
    return (NULL);
}

/**
 * @brief Change to a directory and update environment variables
 * @param path Path to change to (or environment variable name)
 * @param shell Shell structure
 * @param type 1 for env variable, 2 for direct path, 3 for cd-
 * @return 0 on success, 1 on failure
 */
int change_path(char *path, t_shell *shell, int type)
{
    char    *path_extract = NULL;
    int     ret;
    char    *current_pwd;

    ret = 0;
    current_pwd = get_pwd();
    if (!current_pwd)
        return (1);
    if (type == 1) // Environment variable (HOME= or OLDPWD=)
    {
        path_extract = extract_path(path, shell);
        if (!path_extract)
        {
            free(current_pwd);
            return (1);
        }
        ret = chdir(path_extract);
        // if (ret < 0)
        //     return (0);
        // else
        //     add_path(shell, current_pwd);
        free(path_extract);
    }
    else if (type == 2) //Direct path
    {
        ret = chdir(path);
        // if (ret < 0)
        //     return (0);
        // else
        //     add_path(shell, current_pwd);
    }
    else if (type == 3)  // cd - (print destination)
    {
        path_extract = extract_path("OLDPWD=", shell);
        if (!path_extract)
        {
            free(current_pwd);
            return (1);
        }
        ret = chdir(path_extract);
        if (ret == 0)
        {
            // Print the destination directory (bash behavior)
            printf("%s\n", path_extract);
        }
        free(path_extract);
    }
    else
    {
        free(current_pwd);
        return (1);
    }
    if (ret != 0)
    {
        free(current_pwd);
        return (1);
    }
    // Update PWD and OLDPWD
    if (update_pwd_vars(shell, current_pwd) != 0)
    {
        free(current_pwd);
        return (1);
    }
    free(current_pwd);
    return (0);
}
/**
 * @brief Main ft_cd function - bash cd builtin implementation
 * @param cmd Command structure with arguments
 * @param shell Shell structure
 * @return 0 on success, 1 on failure (bash-compatible)
 */
int    ft_cd(t_commands *cmd, t_shell *shell)
{
    if (!cmd->args[1]) // Case 1: cd (no arguments) - go to HOME
    {
        if (change_path("HOME=", shell, 1) != 0)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
        return (0);
    }
    if (ft_strncmp(cmd->args[1], "-", 2) == 0)     // Case 2: cd - (go to previous directory)
    {
        if (change_path("OLDPWD=", shell, 3) != 0)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            return (1);
        }
        return (0);
    }
    if (ft_strncmp(cmd->args[1], "~", 2) == 0)     // Case 3: cd ~ (go to HOME directory)
    {
        if (change_path("HOME=", shell, 1) != 0)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
        return (0);
    }
    if (change_path(cmd->args[1], shell, 2) != 0)     // Case 4: cd <path> (go to specified directory)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        perror(cmd->args[1]);
        return (1);
    }
    return (0);
}
