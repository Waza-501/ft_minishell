/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/20 12:04:31 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/20 16:36:54 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg)
{
	ft_putstr_fd("minishell$ ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
}

void	*malloc_error(char *msg)
{
	ft_putstr_fd("minishell$ ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": cannot allocate memory\n", STDERR_FILENO);
	return (NULL);
}
