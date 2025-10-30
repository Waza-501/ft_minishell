/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strip_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/22 13:19:53 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/30 16:22:44 by owhearn       ########   odam.nl         */
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

// char	*trim_quotes_str(char *src)
// {
// 	char	*new;

// 	new = NULL;
// 	printf("do I use this\n");
// 	if (!src || is_quotes(src[0]) == false)
// 		return (0);
// 	new = ft_strtrim(src, identify_quotes(src[0]));
// 	if (!new)
// 		return (NULL);
// 	return (new);
// }

int	trim_quotes(t_lexer *node)
{
	char	*new;

	new = NULL;
	if (!node->string || is_quotes(node->string[0]) == false)
		return (0);
	new = ft_strtrim(node->string, identify_quotes(node->string[0]));
	if (!new)
		return (1);
	ft_free (&node->string);
	node->string = new;
	return (0);
}
