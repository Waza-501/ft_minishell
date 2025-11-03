/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/29 12:24:27 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/31 13:19:28 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*to do: make a malloc_error function*/

void	todo_exit(t_data *data)
{
	free_structs(data);
	printf("this should not be used anymore\n");
	exit(1);
}

void	free_structs(t_data *data)
{
	cdll_del_list(data->envp_copy);
	ft_free(&data->input);
	if (data->lexer)
		clear_lexer(data);
	if (data->commands)
		clear_commands(data);
	ft_free(&data);
}

void	perror_exit(t_data *data)
{
	perror("minishell: ");
	free_structs(data);
	exit(errno);
}

void	*malloc_error(t_data *data, bool print)
{
	if (print == true)
		malloc_error_print("malloc");
	if (!data)
		return (NULL);
	free_structs(data);
	exit(1);
}
