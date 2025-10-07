/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_error.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/29 12:24:27 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/07 11:01:28 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*to do: make a malloc_error function*/

void	todo_exit(t_data *data)
{
	free_structs(data, NULL);
	exit(1);
}

void	free_structs(t_data *data, t_commands *list)
{
	cdll_del_list(data->envp_copy);
	clear_lexer(data);
	free(data->input);
	if (list)
		clear_commands(list);
	free(data);
}
