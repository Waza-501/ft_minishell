/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: owhearn <owhearn@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/24 15:47:52 by owhearn       #+#    #+#                 */
/*   Updated: 2025/10/24 15:48:22 by owhearn       ########   odam.nl         */
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
		return (malloc_error(NULL, true));
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
