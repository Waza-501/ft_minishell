/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 12:40:57 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/03 16:25:45 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*init_commands(void)
{
	t_commands	*new;

	new = (t_commands *)malloc(sizeof(t_commands));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->infile_s = NULL;
	new->outfile_s = NULL;
	new->infile = -1;/*potentially set this to stdin*/
	new->outfile = -1;/*potentially set this to stdout*/
	new->infiles = NULL;
	new->outfiles = NULL;	
	new->next = NULL;
	new->prev = NULL;
	//new fields for execution
	new->n = 0;
	new->pid = -1;
	new->pipefd[0] = -1;
	new->pipefd[1] = -1;
	return (new);
}

t_commands	*command_list_last(t_commands *list)
{
	t_commands	*copy;

	copy = list;
	while (copy->next)
		copy = copy->next;
	return (copy);
}

int	add_command_node(t_commands	**list)
{
	t_commands	*new;
	t_commands	*last;

	new = init_commands();
	if (!new)
		return (1);
	if (!*list)
	{
		*list = new;
		return (0);
	}
	last = command_list_last(*list);
	last->next = new;
	new->prev = last;
	return (0);
}
