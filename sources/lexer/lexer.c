/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 20:28:55 by owen          #+#    #+#                 */
/*   Updated: 2025/10/24 16:19:28 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	to_be_split(t_lexer *node)
{
	int	idx;

	idx = 0;
	while (node->string[idx])
	{
		if (node->string[idx] == '|')
			if (node->string[idx + 1] || idx != 0)
				return (idx);
		idx++;
	}
	return (0);
}

int	split_pipes(t_data *data)
{
	t_lexer	*copy;
	int		i;

	copy = data->lexer;
	while (copy)
	{
		i = to_be_split(copy);
		if (i)
		{
			printf("%s must be split\n", copy->string);

		}
		copy = copy->next;
	}
	return (0);
}

bool	setup_lexer(t_data *data)
{
	char	*copy;
	int		idx;

	copy = ft_strdup(data->input);
	if (!copy)
		return (malloc_error(data, true), false);
	idx = 0;
	while (copy[idx])
	{
		while (is_whitespace(copy[idx]))
			idx++;
		if (copy[idx])
			idx += add_lex_node(&copy[idx], &(data->lexer));
		if (idx == -1)
		{
			ft_free (&copy);
			malloc_error(data, false);
		}
	}
	ft_free (&copy);
	if (split_pipes(data))
		return (false);
	return (true);
}
