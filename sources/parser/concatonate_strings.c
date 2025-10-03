/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   concatonate_strings.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/09 11:04:04 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/03 15:56:43 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quotes(char c)
{
	if (c && (c == '\'' || c == '\"'))
		return (true);
	return (false);
}

char	*identify_quotes(char c)
{
	if (c == '\'')
		return ("\'");
	return ("\"");
}

/**
 * @brief Removes surrounding quotes from the node's string if present.
 *
 * @param node Pointer to the t_token node.
 * @return int 0 on success, 1 on memory allocation failure.
 */
int	trim_quotes(t_token *node)
{
	char	*new;

	new = NULL;
	if (!node->string || is_quotes(node->string[0]) == false)
		return (0);
	new = ft_strtrim(node->string, identify_quotes(node->string[0]));
	if (!new)
		return (1);
	free (node->string);
	node->string = new;
	return (0);
}
/**
 * @brief Merges the string of the given token node with its next node.
 *
 * This function concatenates the string of the current node with the string
 * of its next node, updates the current node's string, copies the concat flag,
 * and removes the next node from the linked list. It also trims quotes from
 * the next node before merging.
 *
 * @param node Pointer to the current t_token node. Must have a valid next node.
 * @return int Returns 0 on success, 1 on failure (e.g., memory allocation error).
 */
int	merge_nodes(t_token *node)
{
	char	*new;

	if (trim_quotes(node->next))
		return (1);
	new = ft_strjoin(node->string, node->next->string);
	if (!new)
		return (1);
	free(node->string);
	node->string = new;
	node->concat = node->next->concat;
	lex_del_node(node->next);
	return (0);
}

/**
 * @brief Concatenates strings of token nodes in a linked list where needed.
 *
 * Iterates through the linked list of t_token nodes. For each node whose string
 * starts with a quote, trims the quotes and merges with subsequent nodes marked
 * for concatenation. Updates the concat flag and removes merged nodes.
 *
 * @param list Pointer to the head of the t_token linked list.
 * @return int Returns 0 on success, 1 on failure (e.g., memory allocation error).
 */
int	concatonate_strings(t_token	*list)
{
	t_token	*copy;

	copy = list;
	while (copy)
	{
		if (copy && is_quotes(copy->string[0]) == true)
		{
			if (trim_quotes(copy))
				return (1);
			while (copy->concat == true)
			{
				copy->concat = false;
				if (merge_nodes(copy))
					return (1);
			}
		}
		copy = copy->next;
	}
	return (0);
}

bool	concatonate_redirect(t_data *data)
{
	t_token		*copy;

	copy = data->lexer;
	if (concatonate_strings(copy))
		return (false);
	while (copy->next)
	{
		if (copy->type > 3)
			set_redirect(copy);
		copy = copy->next;
	}
	return (true);
}
