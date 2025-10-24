/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_list_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 12:41:20 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/24 16:31:00 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_list(t_commands *list)
{
	int			idx;
	int			i;
	t_commands	*copy;

	copy = list;
	i = 1;
	while (copy)
	{
		idx = 0;
		printf("node %i: [", i);
		if (copy->args)
		{
			while (copy->args[idx])
			{
				printf("%s", copy->args[idx]);
				idx++;
				if (copy->args[idx])
					printf(", ");
			}
		}
		printf("] infile [%s] outfile [%s]\n", copy->infile_s, copy->outfile_s);
		copy = copy->next;
		i++;
	}
}

void	clear_commands(t_data *data)
{
	t_commands	*start;

	start = data->commands;
	while (data->commands != NULL)
	{
		start = data->commands->next;
		ft_free_arr(data->commands->args);
		ft_free(&data->commands->infile_s);
		if (data->commands->infile > 2)
		{
			if (close(data->commands->infile))
				printf("write fail free error report thing using perror\n");
		}
		ft_free(&data->commands->outfile_s);
		if (data->commands->outfile > 2)
		{
			if (close(data->commands->outfile))
				printf("write fail free error report thing using perror\n");
		}
		ft_free(&data->commands);
		data->commands = start;
	}
}
