/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_list_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 12:41:20 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/18 16:06:03 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_commands(t_data *data)
{
	t_commands	*start;

	start = data->commands;
	while (data->commands != NULL)
	{
		start = data->commands->next;
		ft_free_arr(data->commands->args);
		if (data->commands->infile > 2)
		{
			if (close(data->commands->infile))
				printf("write fail free error report thing using perror\n");
		}
		if (data->commands->outfile > 2)
		{
			if (close(data->commands->outfile))
				printf("write fail free error report thing using perror\n");
		}
		delete_files_list(data->commands);
		ft_free(&data->commands);
		data->commands = start;
	}
}
