/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/03 15:14:25 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 08:33:44 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*new_files_node(char *str)
{
	t_files	*new;

	if (!str)
		return (malloc_error(NULL, true));
	new = (t_files *)malloc(sizeof(t_files));
	if (!new)
		return (malloc_error(NULL, true));
	new->filename = str;
	new->type = EMPTY;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files	*get_last_file(t_files *list)
{
	t_files	*copy;

	copy = list;
	while (copy->next)
		copy = copy->next;
	return (copy);
}

int	add_file_node(t_files **list, t_lexer *lexer)
{
	t_files	*new;
	t_files	*copy;

	new = new_files_node(ft_strdup(lexer->string));
	if (!new)
		return (1);
	if (!*list)
	{
		*list = new;
		return (0);
	}
	copy = get_last_file(list);
	copy->next = new;
	new->prev = copy;
	return (0);
}