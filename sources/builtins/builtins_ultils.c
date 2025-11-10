/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_ultils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 13:57:55 by haile         #+#    #+#                 */
/*   Updated: 2025/11/10 14:50:08 by haile         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
