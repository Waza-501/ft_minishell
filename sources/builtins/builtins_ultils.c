/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_ultils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 13:57:55 by haile         #+#    #+#                 */
/*   Updated: 2025/11/10 12:42:48 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modify_path(t_shell *shell, char *temp, int code, int code2)
{
	if (code)
		ft_export(0, shell, "OLDPWD=");
	else if (code2)
		ft_export(0, shell, "PWD=");
	return (0);
}

/**
 * @brief Get current working directory
 * @return Allocated string with current directory or NULL on failure
 */
char	*get_pwd(void)
{
	char	*buf;

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
