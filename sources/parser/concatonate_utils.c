/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   concatonate_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 10:11:20 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/06 11:29:00 by owhearn       ########   odam.nl         */
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
 * @param node Pointer to the t_lexer node.
 * @return int 0 on success, 1 on memory allocation failure.
 */
int	trim_quotes(t_lexer *node)
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
