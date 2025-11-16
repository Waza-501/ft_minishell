/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: haile < haile@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 13:57:55 by haile         #+#    #+#                 */
/*   Updated: 2025/11/16 09:16:07 by haile         ########   odam.nl         */
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

/**
 * @brief Print long error message for getcwd failure
 */
void	print_getcwd_error(void)
{
	ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
	ft_putendl_fd("getcwd: cannot access parent directories", STDERR_FILENO);
}
