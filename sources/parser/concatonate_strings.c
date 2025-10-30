/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   concatonate_strings.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/09 11:04:04 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/30 17:41:46 by owhearn       ########   odam.nl         */
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

	if (!node->next)
		return (1); /*implement error logging*/
	new = ft_strjoin(node->string, node->next->string);
	if (!new)
		return (1); /*implement error logging*/
	ft_free(&node->string);
	node->string = new;
	node->concat = node->next->concat;
	lex_del_node(node->next);
	return (0);
}

int	configure_redirect(t_lexer *node)
{
	int		idx;
	char	*tmp;

	if (node->type == INPUT || node->type == OUTPUT)
		idx = 1;
	else
		idx = 2;
	if ((int)ft_strlen(node->string) == idx)
	{
		ft_bzero(node->string, idx);
		if (node->next && node->next->type == PIPE)
			return (0);
		if (merge_nodes(node))
			return (1);
	}
	else
	{
		tmp = ft_strdup(&node->string[idx]);
		ft_free(node->string);
		node->string = tmp;
		if (!node->string)
			return (1);
	}
	return (0);
}

/*rework documentation*/
bool	concatonate_strings(t_lexer	*list)
{
	t_lexer	*copy;

	copy = list;
	while (copy)
	{
		if (copy && copy->concat == true)
		{
			while (copy->concat == true)
			{
				if (trim_quotes(copy) || trim_quotes(copy->next))
					return (false);
				copy->concat = false;
				if (merge_nodes(copy))
					return (false);
			}
		}
		// else if (copy && copy->type > 3)
		// {
		// 	if (configure_redirect(copy))
		// 		return (false);
		// }
		if (trim_quotes(copy))
			return (false);
		copy = copy->next;
	}
	return (true);
}
