/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_list_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 12:41:20 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/07 11:19:34 by owhearn       ########   odam.nl         */
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
		while (copy->args[idx])
		{
			printf("%s", copy->args[idx]);
			idx++;
			if (copy->args[idx])
				printf(", ");
		}
		printf("]\n");
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
			close(list->infile);
		if (list->outfile > 2)
			close(list->outfile);
		free(list);
		list = start;
	}
}
