/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/20 12:04:31 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/30 13:51:02 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*add : ft_putstr_fd("syntax error: unexpected end of file", STDERR_FILENO)*/
/*add : ft_putstr_fd("syntax error near unexpected token `|'", STDERR_FILENO)
		with token being pipe, or redirects*/
void	print_syntax_error(char *msg, char *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

void	print_error(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
}

void	*malloc_error_print(char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": cannot allocate memory\n", STDERR_FILENO);
	return (NULL);
}
