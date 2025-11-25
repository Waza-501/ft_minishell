/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_list_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 12:41:20 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/25 12:28:47 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

void	clear_commands(t_data *data)
{
	t_commands	*start;

	start = data->commands;
	while (data->commands != NULL)
	{
		start = data->commands->next;
		ft_free_arr(data->commands->args);
		close_all_fd(data->commands, 0, NULL);
		delete_files_list(data->commands);
		ft_free(&data->commands);
		data->commands = start;
	}
}
