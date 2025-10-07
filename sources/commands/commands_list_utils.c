/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_list_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 12:41:20 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/07 14:15:37 by owhearn       ########   odam.nl         */
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
		else
			printf("no args? :(");
		printf("]");
		printf(" infile [%s]", copy->infile_s);
		printf(" outfile [%s]\n", copy->outfile_s);
		copy = copy->next;
		i++;
	}
}

void	clear_commands(t_commands *list)
{
	t_commands	*start;

	start = list;
	while (list != NULL)
	{
		start = list->next;
		ft_free_arr(list->args);
		if (list->infile > 2)
		{
			ft_free(list->infile_s);
			if (close(list->infile))
				printf("write fail free error report thing\n");
		}
		if (list->outfile > 2)
		{
			ft_free(list->outfile_s);
			if (close(list->outfile))
				printf("write fail free error report thing\n");
		}
		free(list);
		list = start;
	}
}
