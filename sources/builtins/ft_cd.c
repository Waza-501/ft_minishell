/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:23:18 by haile         #+#    #+#                 */
/*   Updated: 2025/10/24 10:00:24 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int add_path(t_shell *shell, char *new_path)
{
    int i;
    int old;
    int p;
    char *pwd;

    i = 0;
    old = 1;
    p = 2;
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], "PWD", 3) == 0)
        {
            free(shell->env[i]);
            pwd = get_pwd();
            if (!pwd)
                return (-1);
            shell->env[i] = ft_strjoin("PWD=", pwd);
            p = 0;
        }
        else if (ft_strncmp(shell->env[i], "OLDPWD", 6) == 0)
        {
            free(shell->env[i]);
            shell->env[i] = ft_strjoin("OLDPWD=", pwd);
            old = 0;
        }
        i++;
    }
    if (old || p)
        modify_path(shell, pwd, old, p);
    return (0);
}
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
    return (0);
}

int change_path(char *path, t_shell *shell, int type)
{
    char    *path_extract;
    int     ret;
    char    *current_pwd;

    ret = 0;
    current_pwd = get_pwd();
    if (type == 1)
    {
        path_extract = extract_path(path, shell);
        if (!path_extract)
            return (0);
        ret = chdir(path_extract);
        if (ret < 0)
            return (0);
        else
            add_path(shell, current_pwd);
    }
    else if (type == 2)
    {
        ret = chdir(path);
        if (ret < 0)
            return (0);
        else
            add_path(shell, current_pwd);
    }
    return (1);
}
int    ft_cd(t_commands *cmd, t_shell *shell)
{
    char	*path;
    int		ret;

    if (!cmd->args[1])
    {
        if (!change_path("HOME=", shell, 1))
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
    }
    else if (cmd->args[1])
    {
        if (ft_strncmp(cmd->args[1], "-", 1) == 0)
        {
            if (!change_path("OLDPWD=", shell, 1))
                ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
        }
        else
        {
            if (!change_path(cmd->args[1], shell, 2))
            {
                ft_putstr_fd("minishell: cd: ", 2);
                perror(cmd->args[1]);
                return (1); 
            }
        }
    }
    return (1);
}