/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: owen <owen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/28 20:28:55 by owen          #+#    #+#                 */
/*   Updated: 2025/10/03 16:10:16 by owhearn       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_delim(char *str, char delim)
{
	size_t	size;

	size = 0;
	if (delim == S_Q || delim == D_Q)
		size++;
	while (str[size] && str[size] != delim)
		size++;
	if (delim == SPACE)
		return (size);
	return (size + 1);
}

char	*strcpy_delim(char *str, char delim1, char delim2, char delim3)
{
	size_t	idx;
	size_t	size;
	char	*new;

	idx = 0;
	size = 0;
	if (is_quotes(delim1) == true)
		size = ft_strlen_delim(str, delim1);
	else
		while (str[size] && str[size] != delim1 && str[size] != delim2
			&& str[size] != delim3)
			size++;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (idx < size)
	{
		new[idx] = str[idx];
		idx++;
	}
	new[idx] = '\0';
	return (new);
}

bool	id_token(char *str)
{
	int		idx;

	idx = 0;
	if (str[idx] == '|')
		return (true);
	else if (str[idx] == '<')
		return (true);
	else if (str[idx] == '>')
		return (true);
	return (false);
}

bool	setup_lexer(t_data *data)
{
	char	*copy;
	int		idx;

	copy = ft_strdup(data->input);
	if (!copy)
		exit (1);
	idx = 0;
	while (copy[idx])
	{
		while (is_whitespace(copy[idx]))
			idx++;
		if (copy[idx])
			idx += add_lex_node(&copy[idx], &(data->lexer));
	}
	free (copy);
	return (true);
}
