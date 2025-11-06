/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   files_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/03 15:14:25 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/06 12:46:57 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

static t_files	*new_files_node(t_lexer *lexer)
{
	t_files	*new;
	char	*str;

	new = (t_files *)malloc(sizeof(t_files));
	if (!new)
		return (malloc_error(NULL, true));
	str = ft_strdup(lexer->string);
	if (!str)
		return (ft_free(&new), malloc_error(NULL, true));
	new->type = lexer->type;
	new->hd_delim = NULL;
	if (new->type == HEREDOC)
	{
		new->hd_delim = str;
		new->filename = get_hd_filename();
		if (!new->filename)
			return (ft_free(&new), ft_free(&str), NULL);
	}
	else
		new->filename = str;
	new->open = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_files	*find_open_fd(t_files *list)
{
	t_files	*copy;

	while (copy && copy->open == false)
		copy = copy->next;
	return (copy);
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

	new = new_files_node(lexer);
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
