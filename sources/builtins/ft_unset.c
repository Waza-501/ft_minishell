/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/05 12:00:55 by haile         #+#    #+#                 */
/*   Updated: 2025/09/05 12:05:57 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
            rtn[j++] = ft_strdup(env[i]);
        }
        i++;
    }
}
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

int ft_unset(t_cmds *cmd, t_shell *shell)
{
    int i;
    int j;
    char **rtn;

    j = 1;
    if (!cmd->str[1])
        return (0);
    while (cmd->str[i])
    {
        if (in_env(cmd->str[i], shell->env))
        {
            i = 0;
            while (shell->env[i])
                i++;
            rtn = ft_calloc((ft_arrlen(shell->env)), sizeof(char *));
            if (!rtn)
                return (-1);
            unset_array(shell->env, rtn, cmd->str[i]);
            ft_free_arr(shell->env);
            shell->env = rtn;
        }
        j++;
    }
    return (0);
}