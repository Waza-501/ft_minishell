/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 20:28:55 by owen          #+#    #+#                 */
/*   Updated: 2025/11/03 14:48:10 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_token(t_lexer *node, int n)
{
	char	*old;
	char	*new;

	if (n == 0)
	{
		old = ft_substr(node->string, 0, 2);
		new = ft_strdup(&node->string[2]);
	}
	else
	{
		old = (char *)malloc((size_t)n + 1);
		new = ft_strdup(&node->string[n]);
	}
	if (!new || !old)
	{
		ft_free(&new);
		ft_free(&old);
		malloc_error(NULL, true);
		return (-1);
	}
	if (n != 0)
		ft_strlcpy(old, node->string, (size_t)n + 1);
	return (insert_new_node(node, new, old));
}

int	to_be_named(t_lexer	*node, int n)
{
	char	*new;
	char	*old;

	if (node->string[n] == node->string[n + 1] && node->string[n] != '|')
		return (double_token(node, n));
	if (n == 0)
	{
		old = ft_chardup(node->string[0]);
		new = ft_strdup(&node->string[1]);
	}
	else
	{
		old = (char *)malloc((size_t)n + 1);
		new = ft_strdup(&node->string[n]);
	}
	if (!new || !old)
	{
		ft_free(&new);
		ft_free(&old);
		malloc_error(NULL, true);
		return (-1);
	}
	if (n != 0)
		ft_strlcpy(old, node->string, (size_t)n + 1);
	return (insert_new_node(node, new, old));
}

int	find_pipe_in_string(char *str)
{
	int	idx;

	idx = 0;
	if (ft_strlen(str) == 1 || (str[idx] == S_Q || str[idx] == D_Q))
		return (-1);
	else if (ft_strlen(str) == 2 && (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2)))
		return (-1);
	while (str[idx])
	{
		if (str[idx] == '|' || str[idx] == '<' || str[idx] == '>')
			return (idx);
		idx++;
	}
	return (-1);
}

int	split_operators(t_data *data)
{
	t_lexer	*copy;
	int		i;

	copy = data->lexer;
	while (copy)
	{
		i = find_pipe_in_string(copy->string);
		if (i >= 0)
			if (to_be_named(copy, i))
				malloc_error(data, false);
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
	if (split_operators(data))
		return (false);
	return (true);
}
