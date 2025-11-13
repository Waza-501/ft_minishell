/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/29 12:24:27 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/11 15:55:30 by owhearn       ########   odam.nl         */
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

void	perror_exit(t_data *data)
{
	perror("minishell: ");
	free_data(data);
	exit(errno);
}

void	*malloc_error(t_data *data, bool print)
{
	if (print == true)
		malloc_error_print("malloc");
	if (!data)
		return (NULL);
	printf("exit time\n");
	free_data(data);
	exit(1);
}
