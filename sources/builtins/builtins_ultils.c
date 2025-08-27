/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_ultils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile <haile@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 13:57:55 by haile         #+#    #+#                 */
/*   Updated: 2025/08/27 14:01:09 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int    modify_path(t_shell *shell, char *temp, int code, int code2)
{
    if (code)
        ft_export(0, shell, "OLDPWD=");
    else if (code2)
        ft_export(0, shell, "PWD=");
    add_path(shell, temp);
    return (0);
}

char    *get_pwd(void)
{
    char    *buf;

    buf = malloc(PATH_MAX * sizeof(*buf));
    if (!buf)
        return (NULL);
    if (getcwd(buf, PATH_MAX))
        return (buf);
    else
    {
        free(buf);
        return (NULL);
    }   
}