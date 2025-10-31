/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   concatonate_strings.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/09 11:04:04 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/31 17:05:45 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Merges the string of the given token node with its next node.
 *
 * This function concatenates the string of the current node with the string
 * of its next node, updates the current node's string, copies the concat flag,
 * and removes the next node from the linked list. It also trims quotes from
 * the next node before merging.
 *
 * @param node Pointer to the current t_lexer node. Must have a valid next node.
 * @return int Returns 0 on success, 
 * 1 on failure (e.g., memory allocation error).
 */
int	merge_nodes(t_lexer *node)
{
	char	*new;

	new = ft_strjoin(node->string, node->next->string);
	if (!new)
		return (malloc_error(NULL, true), 1);
	ft_free(&node->string);
	node->string = new;
	node->concat = node->next->concat;
	lex_del_node(node->next);
	return (0);
}

int	configure_redirect(t_data *data, t_lexer *node)
{
	ft_free(&node->string);
	if (merge_nodes(node))
		malloc_error(data, false);
	return (0);
}

/*rework documentation*/
		// else if (copy && copy->type > 3)
		// {
		// 	if (configure_redirect(copy))
		// 		return (false);
		// }
/*us this snippet for setting up redirection

A heredoc must start and end with a quote, if one is given.
Otherwise, this is a syntax error*/
bool	concatonate_strings(t_data *data)
{
	t_lexer	*copy;

	copy = data->lexer;
	while (copy)
	{
		if (copy && copy->type > 3)
			configure_redirect(data, copy);
		if (copy && copy->concat == true)
		{
			while (copy->concat == true)
			{
				if (trim_qt(copy, EMPTY) || trim_qt(copy->next, copy->type))
					malloc_error(data, false);
				copy->concat = false;
				if (merge_nodes(copy))
					malloc_error(data, false);
			}
		}
		if (copy->type < 3)
			if (trim_qt(copy, EMPTY))
				malloc_error(data, false);
		copy = copy->next;
	}
	return (true);
}
