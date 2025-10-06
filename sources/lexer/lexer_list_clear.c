/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_list_clear.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/12 10:45:22 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/06 13:16:16 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_del_node(t_lexer *node)
{
	if (node->next != NULL)
		node->next->prev = node->prev;
	node->prev->next = node->next;
	if (node->string)
		free(node->string);
	free (node);
	node = NULL;
}

void	lex_del_first(t_data *data)
{
	t_lexer	*new_head;
	t_lexer	*old_head;

	new_head = data->lexer->next;
	new_head->prev = NULL;
	old_head = data->lexer;
	if (old_head->string)
		free(old_head->string);
	free(old_head);
	data->lexer = new_head;
}

void	clear_lexer(t_data *data)
{
	t_lexer	*start;

	start = data->lexer;
	while (data->lexer != NULL)
	{
		start = data->lexer->next;
		free(data->lexer->string);
		free(data->lexer);
		data->lexer = start;
	}
}
