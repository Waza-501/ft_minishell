/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/04 13:13:56 by owhearn       #+#    #+#                 */
/*   Updated: 2025/11/04 16:08:24 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quotes(char c)
{
	if (c && (c == '\'' || c == '\"'))
		return (true);
	return (false);
}

bool	is_token(char *str)
{
	int		idx;

	idx = 0;
	if (str[idx] == '|' || str[idx] == '<' || str[idx] == '>')
		return (true);
	return (false);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f');
}

bool	is_space(const char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!is_whitespace(*str))
			return (false);
		str++;
	}
	return (true);
}
