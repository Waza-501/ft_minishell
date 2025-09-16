/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 12:00:55 by haile         #+#    #+#                 */
/*   Updated: 2025/09/16 13:35:17 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Copy environment array excluding specified variable
 * @param env Source environment array
 * @param rtn Destination array (pre-allocated)
 * @param str Variable name to exclude
 */
static void unset_array(char **env, char **rtn, char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], str, ft_strlen(str)) != 0)
        {
            rtn[j] = ft_strdup(env[i]);
            if (!rtn[j])
            {
                ft_free_arr(rtn);
                return ;
            }
            j++;
        }
        i++;
    }
}
/**
 * @brief Check if variable exists in environment
 * @param str Variable name to search for
 * @param env Environment array
 * @return true if found, false otherwise
 */
static bool in_env(char *str, char **env)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str);
    while (env && env[i])
    {
        if (ft_strncmp(env[i], str, len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
            return (true);
        i++;
    }
    return (false);
}
/**
 * @brief Unset environment variables
 * @param cmd Command structure
 * @param shell Shell state
 * @return 0 on success, -1 on error
 */
int ft_unset(t_cmds *cmd, t_shell *shell)
{
    int i;
    int j;
    char **rtn;

    j = 1;
    if (!cmd->str[1])
        return (0);
    while (cmd->str[j])
    {
        if (in_env(cmd->str[j], shell->env))
        {
            i = 0;
            while (shell->env[i])
                i++;
            rtn = ft_calloc(i, sizeof(char *));
            if (!rtn)
                return (-1);
            unset_array(shell->env, rtn, cmd->str[j]);
            ft_free_arr(shell->env);
            shell->env = rtn;
        }
        j++;
    }
    return (0);
}