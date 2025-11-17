/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 13:57:55 by haile         #+#    #+#                 */
/*   Updated: 2025/11/17 12:37:50 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
