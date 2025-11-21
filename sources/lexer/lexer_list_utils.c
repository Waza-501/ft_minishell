/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/12 10:45:22 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/21 11:34:29 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insert_new_node(t_lexer *node, char *new, char *str)
{
	if (lex_add_next(node, new_lex_node(new)))
	{
		ft_free(str);
		malloc_error(NULL, true);
		return (-1);
	}
	ft_free(&node->string);
	node->string = str;
	return (0);
}

void	lex_del_first(t_data *data)
{
	t_lexer	*new_head;
	t_lexer	*old_head;

	if (!data->lexer)
		return ;
	if (data->lexer->next)
	{
		new_head = data->lexer->next;
		new_head->prev = NULL;
	}
	else
		new_head = NULL;
	old_head = data->lexer;
	ft_free(&old_head->string);
	ft_free(&old_head);
	data->lexer = new_head;
}

void	lex_del_node(t_data *data, t_lexer *node)
{
	if (!node->prev)
		return (lex_del_first(data));
	if (node->next != NULL)
		node->next->prev = node->prev;
	node->prev->next = node->next;
	ft_free(&node->string);
	ft_free (&node);
}

void	clear_lexer(t_data *data)
{
	t_lexer	*start;

	start = data->lexer;
	while (data->lexer != NULL)
	{
		start = data->lexer->next;
		ft_free(&data->lexer->string);
		ft_free(&data->lexer);
		data->lexer = start;
	}
}
