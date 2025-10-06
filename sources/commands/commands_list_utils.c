/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_list_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 12:41:20 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/06 13:19:25 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_commands(t_commands	*list)
{
	t_commands	*start;

	start = list;
	while (list != NULL)
	{
		start = list->next;
		ft_free_arr(list->args);
		close(list->infile);
		close(list->outfile);
		ft_free(list);
		list = start;
	}
}
