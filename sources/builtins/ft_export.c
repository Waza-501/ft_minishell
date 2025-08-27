/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 14:02:47 by haile         #+#    #+#                 */
/*   Updated: 2025/08/27 14:11:40 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int check_valid(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '=')
            j = 1;
        i++;
    }
    return (j);
}

char **new_array(char **env, char **rtn, char *str)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (env[i + 1] == NULL)
        {
            rtn[i] = ft_strdup(str);
            rtn[i + 1] = NULL;
        }
        else
            rtn[i] = ft_strdup(env[i]);
        i++;
    }
    if (!rtn[i])
    {
        ft_free_arr(rtn);
        return (rtn);
    }
    return (rtn);
}

int ft_export(t_cmds *cmd, t_shell *shell, char *str)
{
    int i;
    char **temp;
    char **rtn;
    int cd;

    i = 0;
    cd = 0;
    if (str)
        cd = 1;
    if (!str && !cmd->str[1])
    {
        printf("Print env sorted\n");
        return (1);
    }
    else if (!str && ft_strncmp(cmd->str[1], "=", 1) == 0)
    {
        ft_putstr_fd("minishell: export: `=': not a valid identifier\n", 2);
    }
    else if (!check_valid(cmd->str[1]))
        return (1);
    else
    {
        while (shell->env[i])
            i++;
        rtn = ft_calloc(i + 2, sizeof(char *));
        if (cd)
            temp = new_array(shell->env, rtn, str);
        else
            temp = new_array(shell->env, rtn, cmd->str[1]);
        ft_free_arr(shell->env);
        shell->env = temp;
    }
    return (1);
}