/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/03 15:14:25 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 12:02:38 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_files	*new_files_node(char *str)
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

void	delete_files_list(t_commands *cmd)
{
	t_files	*copy;
	t_files	*next;

	copy = cmd->infiles;
	while (copy)
	{
		next = copy->next;
		ft_free(&copy->filename);
		ft_free(&copy);
		copy = next;
	}
	copy = cmd->outfiles;
	while (copy)
	{
		next = copy->next;
		ft_free(&copy->filename);
		ft_free(&copy);
		copy = next;
	}
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
	copy = get_last_file(*list);
	copy->next = new;
	new->prev = copy;
	return (0);
}
